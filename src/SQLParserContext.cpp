//
// Created by David van Laatum on 26/3/17.
//

#include <strings.h>
#include <iostream>
#include "SQLParserContext.h"

SQLParserContext::SQLParserContext ( std::string fileName, SQLParserCallback *callback ) : fileName ( fileName ),
                                                                                           callback ( callback ) {
  errorStream = &std::cerr;
  outStream = &std::cout;
  timestamp = 0;
}

void SQLParserContext::push ( yy::location yylloc, SQLStatement *statement ) {
  out () << yylloc << " " << *statement << std::endl;

  if ( SetStatement *set = dynamic_cast<SetStatement *>(statement) ) {
    for ( SQLObjectList<SetPair *>::const_iterator it = set->getArgs ().begin (); it != set->getArgs ().end (); ++it ) {
      if ( ( *it )->getName () == "TIMESTAMP" ) {
        if ( SQLInteger *t = dynamic_cast<SQLInteger *> (( *it )->getValue ()) ) {
          updateTime ( t->toInt () );
        } else {
          error () << yylloc << " invalid value for timestamp " << ( *it )->getValue () << std::endl;
        }
      }
    }
  }

  if ( callback ) {
    callback->statement ( statement, this );
  }

  delete statement;
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

void SQLParserContext::updateDB ( std::string db ) {
  if ( db.at ( 0 ) == '`' ) {
    db.erase ( 0, 1 );
    db.erase ( db.end () );
  }

  out () << "DB is now " << db << std::endl;
}

void SQLParserContext::updateTime ( time_t timestamp ) {
  if ( this->timestamp != timestamp ) {
    out () << "Now at " << timestamp << std::endl;
  }
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
