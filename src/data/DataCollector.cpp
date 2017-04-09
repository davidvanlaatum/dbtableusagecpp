//
// Created by David van Laatum on 1/4/17.
//

#include <location.hh>
#include <boost/date_time.hpp>
#include <SQLBeginStatement.h>
#include <SQLCommitStatement.h>
#include <SQLRollbackStatement.h>
#include "DataCollector.h"
#include "SQLParserContext.h"
#include "SQLSetStatement.h"
#include <byteutils.h>
#include <timeutils.h>

using namespace boost::posix_time;
using namespace boost::local_time;

DataCollector::DataCollector () {
  host = boost::shared_ptr<Host> ( new Host () );
  bzero ( &lastUpdate, sizeof ( lastUpdate ) );
  bzero ( &start, sizeof ( start ) );
  bzero ( &now, sizeof ( now ) );
  bzero ( &last, sizeof ( last ) );
  currentFileSize = 0;
  pStore = NULL;
  inTransaction = false;
  commitInterval = 10;
  progress = &std::cerr;
  output = &std::cerr;
}


typedef SQL::SQLSetStatement::ArgsType SetArgs;

void DataCollector::statement ( yy::location &location, SQL::SQLStatement *statement, SQL::SQLParserContext *context ) {
  if ( SQL::SQLSetStatement *set = dynamic_cast<SQL::SQLSetStatement *> (statement) ) {
    for ( SetArgs::const_iterator it = set->getArgs ().begin (); it != set->getArgs ().end (); ++it ) {
      if ( ( *it )->getValue () ) {
        variables[( *it )->getName ()] = boost::shared_ptr<SQL::SQLObject> ( ( *it )->getValue ()->clone () );
      }
    }
  }

  now.statements++;

  if ( dynamic_cast<SQL::SQLBeginStatement *> ( statement) ) {
    inTransaction = true;
    now.transactions++;
  } else if ( dynamic_cast<SQL::SQLCommitStatement * > (statement) || dynamic_cast<SQL::SQLRollbackStatement *>(statement) ) {
    inTransaction = false;
  }

  now.time = context->currentTime ();
  now.logPos = context->getLogPos ();

  Walker walker ( host, context );
  walker.walk ( statement );
  timeval currentTime;
  gettimeofday ( &currentTime, NULL );

  if ( start.statement == 0 && context->currentTime () != 0 ) {
    start.statement = context->currentTime ();
    start.time = currentTime;
  }

  if ( lastUpdate.tv_sec < currentTime.tv_sec - commitInterval && !inTransaction ) {
    doProgress ( &location, context, currentTime );
  }
}

void DataCollector::doProgress ( const location *location, SQL::SQLParserContext *context, timeval &currentTime ) {
  if ( location && location->begin.filename ) {
    host->setLastLogFile ( *location->begin.filename );
  }
  host->setLastLogPos ( (int) context->getLogPos () );
  time_t diff = context->currentTime () - start.statement;
  timeval timeDiff;
  timersub ( &currentTime, &start.time, &timeDiff );
  timeval interval;
  timersub ( &currentTime, &lastUpdate, &interval );

  double speed = diff / ( timeDiff.tv_sec + ( timeDiff.tv_usec / 1000000.0f ) );
  double bspeed = 0;

  if ( last.time != 0 ) {
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

    if ( last.logPos > 0 ) {
      uint64_t bdiff = context->getLogPos () - last.logPos;
      bspeed = bdiff / ( interval.tv_sec + ( interval.tv_usec / 1000000.0f ) );
    }

    *progress << std::setprecision ( 4 );
    *progress << toString ( context->currentTime () )
              << " stmts: " << now.statements << "(" << now.statements - last.statements << ")"
              << " trans: " << now.transactions << "(" << now.transactions - last.transactions << ")"
              << " speed: " << std::setw ( 7 ) << speed << units
              << " " << bytesToString ( bspeed ) << "/s"
              << " logpos: " << bytesToString ( context->getLogPos () ) << logPosExtra.str ();

    if ( pStore ) {
      pStore->save ( *host );
      *progress << " Saved: " << pStore->getSaveCount ();
    }

    if ( location ) {
      *progress << " " << *location;
    }
    *progress << "\n";
  }
  lastUpdate = currentTime;
  last = now;
}

#define COLWIDTH 22

void DataCollector::dump () {
  *output << "Variables" << std::endl;

  for ( variables_type::iterator it = variables.begin (); it != variables.end (); ++it ) {
    *output << it->first << " = " << it->second << std::endl;
  }

  *output << "Tables" << std::endl;
  *output << std::left;

  std::list<DB *> dbs;
  host->getDBs ( dbs );
  for ( std::list<DB *>::iterator itd = dbs.begin (); itd != dbs.end (); ++itd ) {
    *output << std::setfill ( '_' );
    *output << std::setw ( 50 ) << ( *itd )->getName ()
              << std::setw ( COLWIDTH ) << "Created"
              << std::setw ( COLWIDTH ) << "Read"
              << std::setw ( COLWIDTH ) << "Write"
              << std::setw ( COLWIDTH ) << "Insert"
              << std::setw ( COLWIDTH ) << "Update"
              << std::setw ( COLWIDTH ) << "Delete"
              << std::setw ( COLWIDTH ) << "Alter"
              << std::endl;
    *output << std::setfill ( ' ' );
    std::list<Table *> tables;
    ( *itd )->getTables ( tables );
    for ( std::list<Table *>::iterator itt = tables.begin (); itt != tables.end (); ++itt ) {
      *output << std::setw ( 50 ) << ( "  " + ( *itt )->getName () )
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
    *output << "Host " << host->getName () << " does not exist, creating" << std::endl;
    pStore->save ( *host.get () );
  }
  this->pStore = pStore;
}

Host *DataCollector::getHost () const {
  return host.get ();
}

void DataCollector::setCommitInterval ( size_t interval ) {
  this->commitInterval = interval;
}

void DataCollector::setProgressStream ( std::ostream *progress ) {
  DataCollector::progress = progress;
}

void DataCollector::setOutputStream ( std::ostream *output ) {
  DataCollector::output = output;
}

void DataCollector::endOfFile ( SQL::SQLParserContext *context ) {
  timeval currentTime;
  gettimeofday ( &currentTime, NULL );
  doProgress ( NULL, context, currentTime );
  bzero ( &last, sizeof ( last ) );
  bzero ( &now, sizeof ( now ) );
  currentFileSize = 0;
}

DataCollector::Walker::Walker ( boost::shared_ptr<Host> &host, SQL::SQLParserContext *context ) : host ( host ),
                                                                                             ctx ( context ) {
}

void DataCollector::Walker::walk ( SQL::SQLObject *object ) {
  time_t now = ctx->currentTime ();
  if ( SQL::SQLStatement *statement = dynamic_cast<SQL::SQLStatement *> ( object ) ) {
    SQL::SQLStatement::table_type tables;
    statement->getTables ( tables );
    for ( SQL::SQLStatement::table_type::iterator it = tables.begin (); it != tables.end (); it++ ) {
      if ( it->first ) {
        if ( !it->first->getSchema () ) {
          ctx->error () << "No schema on " << it->first << std::endl;
        } else {
          SQL::SQLIdentifier *schema = it->first->getSchema ().get ();
          std::string schemaName = schema->getId ();
          DB *db = host->getDB ( schemaName );
          Table *table = db->getTable ( it->first->getName ()->getId () );
          if ( it->second & SQL::SQLStatement::WRITE ) {
            table->updateWrite ( now );
          }
          if ( it->second & SQL::SQLStatement::READ ) {
            table->updateRead ( now );
          }
          if ( it->second & SQL::SQLStatement::INSERT ) {
            table->updateInsert ( now );
          }
          if ( it->second & SQL::SQLStatement::UPDATE ) {
            table->updateUpdate ( now );
          }
          if ( it->second & SQL::SQLStatement::DELETE ) {
            table->updateDelete ( now );
          }
          if ( it->second & SQL::SQLStatement::ALTER ) {
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
