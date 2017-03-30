//
// Created by David van Laatum on 26/3/17.
//

#include <iostream>
#include "SQLParserContext.h"

SQLParserContext::SQLParserContext ( std::string fileName, SQLParserCallback *callback ) : fileName ( fileName ),
                                                                                           callback ( callback ) {
  errorStream = &std::cerr;
  outStream = &std::cout;
}

void SQLParserContext::push ( yy::location yylloc, SQLStatement *statement ) {
  std::cout << yylloc << " " << *statement << std::endl;

  if ( SetStatement *set = dynamic_cast<SetStatement *>(statement) ) {
    for ( auto item : set->getArgs () ) {
      if ( item->getName () == "TIMESTAMP" ) {
        if ( SQLInteger *t = dynamic_cast<SQLInteger *> (item->getValue ()) ) {
          updateTime ( t->toInt () );
        } else {
          std::cerr << yylloc << " invalid value for timestamp " << item->getValue () << std::endl;
        }
      }
    }
  }

  if ( callback ) {
    callback->statement ( statement, this );
  }

  delete statement;
}

const std::string &SQLParserContext::getFileName () const {
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
    db.pop_back ();
  }

  std::cout << "DB is now " << db << std::endl;
}

void SQLParserContext::updateTime ( time_t timestamp ) {
  if ( this->timestamp != timestamp ) {
    std::cout << "Now at " << timestamp << std::endl;
  }
  this->timestamp = timestamp;
}

void SQLParserContext::setErrorStream ( std::ostream *stream ) {

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
