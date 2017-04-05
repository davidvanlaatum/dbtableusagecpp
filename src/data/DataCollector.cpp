//
// Created by David van Laatum on 1/4/17.
//

#include <location.hh>
#include <boost/date_time.hpp>
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

void DataCollector::statement ( yy::location &location, SQLStatement *statement, SQLParserContext *context ) {
  if ( SQLSetStatement *set = dynamic_cast<SQLSetStatement *> (statement) ) {
    for ( SQLSetStatement::ArgsType::const_iterator it = set->getArgs ().begin (); it != set->getArgs ().end ();
          ++it ) {
      variables[( *it )->getName ()] = boost::shared_ptr<SQLObject> ( ( *it )->getValue ()->clone () );
    }
  }

  statements++;

  Walker walker ( host, context );
  walker.walk ( statement );
  timeval now;
  gettimeofday ( &now, NULL );

  if(firstStatement == 0 && context->currentTime () != 0) {
    firstStatement = context->currentTime ();
    start = now;
  }

  if ( statements % 1000 == 0 || lastUpdate.tv_sec < now.tv_sec - 10 ) {
    time_t diff = context->currentTime () - firstStatement;
    lastTime = context->currentTime ();
    timeval timeDiff;
    timersub ( &now, &start, &timeDiff );

    double speed = diff / ( timeDiff.tv_sec + ( timeDiff.tv_usec / 1000.0f ) );

    std::cerr << toString ( context->currentTime () )
              << " statements: " << statements
              << " speed: " << std::setw ( 15 ) << speed
              << " " << location << "\r";
    lastUpdate = now;
    lastStatements = statements;
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
