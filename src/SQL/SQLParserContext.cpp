//
// Created by David van Laatum on 26/3/17.
//

#include <strings.h>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <boost/scoped_ptr.hpp>
#include "SQLParserContext.h"
#include "SQLParserFailedException.h"
#include "SQLStatement.h"
#include "SQLSetStatement.h"
#include "SQLInteger.h"
#include "SQLUseDatabase.h"

SQLParserContext::SQLParserContext ( std::string fileName, SQLParserCallback *callback ) : fileName ( fileName ),
                                                                                           callback ( callback ),
                                                                                           eventParser ( this ) {
  errorStream = &std::cerr;
  outStream = &std::cout;
  timestamp = 0;
}

void SQLParserContext::push ( yy::location &yylloc, SQLStatement *statement ) {
  boost::scoped_ptr<SQLStatement> autodelete ( statement );
  if ( statement == NULL ) {
    throw SQLParserFailedException ( yylloc, "null statement" );
  }
  statement->resolve ( this );
  if ( verbose ) {
    out () << yylloc << " " << *statement << std::endl;
  }

  if ( SQLSetStatement *set = dynamic_cast<SQLSetStatement *>(statement) ) {
    for ( SQLSetStatement::ArgsType::const_iterator it = set->getArgs ().begin (); it != set->getArgs ().end ();
          ++it ) {
      if ( ( *it )->getName () == "TIMESTAMP" ) {
        if ( SQLInteger *t = dynamic_cast<SQLInteger *> (( *it )->getValue ()) ) {
          updateTime ( t->toInt () );
        } else {
          error () << yylloc << " invalid value for timestamp " << ( *it )->getValue () << std::endl;
        }
      }
    }
  }

  if ( SQLUseDatabase *use = dynamic_cast<SQLUseDatabase *>(statement) ) {
    setCurrentDatabase ( use->getName () );
  }

  callback->statement ( yylloc, statement, this );
}

std::string &SQLParserContext::getFileName () {
  return fileName;
}

void SQLParserContext::print () {
  eventParser.dump ();
}

MySQLEventParser *SQLParserContext::getEventParser () {
  return &eventParser;
}

void SQLParserContext::parseComment ( const char *comment ) {
  if ( strncasecmp ( comment, "# at ", 5 ) == 0 ) {
    logPos = strtoull ( comment + 5, NULL, 10 );
  }
}

void SQLParserContext::updateTime ( time_t timestamp ) {
  this->timestamp = timestamp;
}

void SQLParserContext::setErrorStream ( std::ostream *stream ) {
  errorStream = stream;
}

std::ostream &SQLParserContext::error () const {
  return *errorStream;
}

void SQLParserContext::setOutStream ( std::ostream *ostream ) {
  outStream = ostream;
}

std::ostream &SQLParserContext::out () const {
  return *outStream;
}

void SQLParserContext::error ( location location, std::string msg ) {
  *errorStream << location << ": " << msg << std::endl;
}

boost::shared_ptr<SQLIdentifier> SQLParserContext::getCurrentDatabase () {
  return currentDatabase;
}

void SQLParserContext::setCurrentDatabase ( boost::shared_ptr<SQLIdentifier> name ) {
  currentDatabase = name;
}

time_t SQLParserContext::currentTime () {
  return timestamp;
}

void SQLParserContext::setVerbose ( int verbose ) {
  this->verbose = verbose;
}

int SQLParserContext::getVerbose () const {
  return verbose;
}

void SQLParserContext::setDebug ( int debug ) {
  this->debug = debug;
}

int SQLParserContext::getDebug () const {
  return debug;
}

void yyerror ( location *yylloc, SQLParserContext &ctx, const char *s, ... ) {
  va_list ap;
  va_start( ap, s );
  char *msg = NULL;
  vasprintf ( &msg, s, ap );
  ctx.error ( *yylloc, msg );
  free ( msg );
}

void adjustLines ( location *location, char *text ) {
  char *pos = NULL;
  int lines = 0;
  while ( ( pos = index ( text, '\n' ) ) != NULL ) {
    lines++;
    text = pos + 1;
  }
  if ( lines ) {
    location->lines ( lines );
    location->columns ( (int) strlen ( text ) );
  }
}
