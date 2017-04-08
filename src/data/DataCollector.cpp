//
// Created by David van Laatum on 1/4/17.
//

#include <location.hh>
#include <boost/date_time.hpp>
#include <SQLBeginStatement.h>
#include <SQLCommitStatement.h>
#include <SQLRollbackStatement.h>
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"
#include "DataCollector.h"
#include "SQLStatement.h"
#include "SQLParserContext.h"
#include "SQLSetStatement.h"

using namespace boost::posix_time;
using namespace boost::local_time;
typedef boost::date_time::c_local_adjustor<ptime> local_adj;

DataCollector::DataCollector () {
  host = boost::shared_ptr<Host> ( new Host () );
  statements = 0;
  bzero ( &lastUpdate, sizeof ( lastUpdate ) );
  bzero ( &start, sizeof ( start ) );
  lastStatements = 0;
  lastTime = 0;
  firstStatement = 0;
  currentFileSize = 0;
  pStore = NULL;
  inTransaction = false;
  commitInterval = 10;
  transactions = 0;
  lastTransactions = 0;
}

std::string toString ( time_t t ) {
  std::stringstream s;

  if ( t != 0 ) {
    const ptime &ptime = from_time_t ( t );
    s << local_adj::utc_to_local ( ptime );
  } else {
    s << "never";
  }
  return s.str ();
}

std::string bytesToString ( double value ) {
  std::stringstream s;
  static const char *postfixes[] = { "kb", "mb", "gb", "tb" };
  size_t i = 0;
  const char *postfix = "b";

  while ( value > 1024 && i < ( sizeof ( postfixes ) / sizeof ( postfixes[0] ) ) ) {
    postfix = postfixes[i];
    value /= 1024;
    i++;
  }

  s << std::setprecision ( 3 ) << value << postfix;

  return s.str ();
}

typedef SQLSetStatement::ArgsType SetArgs;

void DataCollector::statement ( yy::location &location, SQLStatement *statement, SQLParserContext *context ) {
  if ( SQLSetStatement *set = dynamic_cast<SQLSetStatement *> (statement) ) {
    for ( SetArgs::const_iterator it = set->getArgs ().begin (); it != set->getArgs ().end (); ++it ) {
      variables[( *it )->getName ()] = boost::shared_ptr<SQLObject> ( ( *it )->getValue ()->clone () );
    }
  }

  statements++;

  if ( dynamic_cast<SQLBeginStatement *> ( statement) ) {
    inTransaction = true;
    transactions++;
  } else if ( dynamic_cast<SQLCommitStatement * > (statement) || dynamic_cast<SQLRollbackStatement *>(statement) ) {
    inTransaction = false;
  }


  Walker walker ( host, context );
  walker.walk ( statement );
  timeval now;
  gettimeofday ( &now, NULL );

  if ( firstStatement == 0 && context->currentTime () != 0 ) {
    firstStatement = context->currentTime ();
    start = now;
  }

  host->setLastLogPos ( (int) context->getLogPos () );

  if ( lastUpdate.tv_sec < now.tv_sec - commitInterval && !inTransaction ) {
    host->setLastLogFile ( *location.begin.filename );
    time_t diff = context->currentTime () - firstStatement;
    timeval timeDiff;
    timersub ( &now, &start, &timeDiff );

    double speed = diff / ( timeDiff.tv_sec + ( timeDiff.tv_usec / 1000000.0f ) );
    double bspeed = 0;

    if ( lastTime != 0 ) {
      std::string units = "s/s";
      if ( speed > 60 ) {
        speed /= 60.0f;
        units = "m/s";
      }
      std::stringstream logPosExtra;
      if ( currentFileSize > 0 ) {
        logPosExtra << std::setprecision ( 3 ) << "/" << bytesToString ( currentFileSize ) << " "
                    << ( ( context->getLogPos () / (double) currentFileSize ) * 100 ) << "%";
      }

      if ( lastLogPos > 0 ) {
        if ( lastLogPos > context->getLogPos () ) {
          lastLogPos = 0;
        }
        uint64_t bdiff = context->getLogPos () - lastLogPos;
        bspeed = bdiff / ( timeDiff.tv_sec + ( timeDiff.tv_usec / 1000000.0f ) );
      }

      std::cerr << std::setprecision ( 4 );
      std::cerr << toString ( context->currentTime () )
                << " statements: " << statements << "(" << statements - lastStatements << ")"
                << " transactions: " << transactions << "(" << transactions - lastTransactions << ")"
                << " speed: " << std::setw ( 7 ) << speed << units
                << " " << bytesToString ( bspeed ) << "/s"
                << " logpos: " << bytesToString ( context->getLogPos () ) << logPosExtra.str ();

      if ( pStore ) {
        pStore->save ( *host );
        std::cerr << " Saved: " << pStore->getSaveCount ();
      }

      std::cerr << " " << location << "\n";
      lastUpdate = now;
    }
    lastTime = context->currentTime ();
    lastStatements = statements;
    lastLogPos = context->getLogPos ();
    lastTransactions = transactions;
  }
}

#define COLWIDTH 22

void DataCollector::dump () {
  std::cout << "Variables" << std::endl;

  for ( variables_type::iterator it = variables.begin (); it != variables.end (); ++it ) {
    std::cout << it->first << " = " << it->second << std::endl;
  }

  std::cout << "Tables" << std::endl;
  std::cout << std::left;

  std::list<DB *> dbs;
  host->getDBs ( dbs );
  for ( std::list<DB *>::iterator itd = dbs.begin (); itd != dbs.end (); ++itd ) {
    std::cout << std::setfill ( '_' );
    std::cout << std::setw ( 50 ) << ( *itd )->getName ()
              << std::setw ( COLWIDTH ) << "Created"
              << std::setw ( COLWIDTH ) << "Read"
              << std::setw ( COLWIDTH ) << "Write"
              << std::setw ( COLWIDTH ) << "Insert"
              << std::setw ( COLWIDTH ) << "Update"
              << std::setw ( COLWIDTH ) << "Delete"
              << std::setw ( COLWIDTH ) << "Alter"
              << std::endl;
    std::cout << std::setfill ( ' ' );
    std::list<Table *> tables;
    ( *itd )->getTables ( tables );
    for ( std::list<Table *>::iterator itt = tables.begin (); itt != tables.end (); ++itt ) {
      std::cout << std::setw ( 50 ) << ( "  " + ( *itt )->getName () )
                << std::setw ( COLWIDTH ) << toString ( ( *itt )->getCreated () )
                << std::setw ( COLWIDTH ) << toString ( ( *itt )->getLastRead () )
                << std::setw ( COLWIDTH ) << toString ( ( *itt )->getLastWrite () )
                << std::setw ( COLWIDTH ) << toString ( ( *itt )->getLastInsert () )
                << std::setw ( COLWIDTH ) << toString ( ( *itt )->getLastUpdate () )
                << std::setw ( COLWIDTH ) << toString ( ( *itt )->getLastDelete () )
                << std::setw ( COLWIDTH ) << toString ( ( *itt )->getLastAlter () )
                << std::endl;
    }
  }
}

void DataCollector::setCurrentFileSize ( uint64_t currentFileSize ) {
  DataCollector::currentFileSize = currentFileSize;
}

void DataCollector::setMonitoredHost ( const std::string &host ) {
  this->host->setName ( host );
}

void DataCollector::setDataStore ( DataStore *pStore ) {
  if ( !pStore->load ( *host.get (), host->getName () ) ) {
    std::cout << "Host " << host->getName () << " does not exist, creating" << std::endl;
    pStore->save ( *host.get () );
  }
  this->pStore = pStore;
}

const Host *DataCollector::getHost () const {
  return host.get ();
}

void DataCollector::setCommitInterval ( size_t interval ) {
  this->commitInterval = interval;
}

DataCollector::Walker::Walker ( boost::shared_ptr<Host> &host, SQLParserContext *context ) : host ( host ),
                                                                                             ctx ( context ) {
}

void DataCollector::Walker::walk ( SQLObject *object ) {
  time_t now = ctx->currentTime ();
  if ( SQLStatement *statement = dynamic_cast<SQLStatement *> ( object ) ) {
    SQLStatement::table_type tables;
    statement->getTables ( tables );
    for ( SQLStatement::table_type::iterator it = tables.begin (); it != tables.end (); it++ ) {
      if ( it->first ) {
        if ( !it->first->getSchema () ) {
          ctx->error () << "No schema on " << it->first << std::endl;
        } else {
          SQLIdentifier *schema = it->first->getSchema ().get ();
          std::string schemaName = schema->getId ();
          DB *db = host->getDB ( schemaName );
          Table *table = db->getTable ( it->first->getName ()->getId () );
          if ( it->second & SQLStatement::WRITE ) {
            table->updateWrite ( now );
          }
          if ( it->second & SQLStatement::READ ) {
            table->updateRead ( now );
          }
          if ( it->second & SQLStatement::INSERT ) {
            table->updateInsert ( now );
          }
          if ( it->second & SQLStatement::UPDATE ) {
            table->updateUpdate ( now );
          }
          if ( it->second & SQLStatement::DELETE ) {
            table->updateDelete ( now );
          }
          if ( it->second & SQLStatement::ALTER ) {
            table->updateAlter ( now );
          }
        }
      }
    }
  }
  if ( object ) {
    object->walk ( this );
  }
}
