//
// Created by David van Laatum on 29/3/17.
//

#include <sstream>
#include "SQLParserFailedException.h"
#include "SQLParserCallback.h"

static std::string join ( const location &location, std::string msg ) {
  std::stringstream str;
  str << location << ": " << msg;
  return str.str ();
}

SQLParserFailedException::SQLParserFailedException ( const std::string &msg ) : runtime_error ( msg ) {

}

SQLParserFailedException::SQLParserFailedException ( const char *msg ) : runtime_error ( msg ) {

}

SQLParserFailedException::SQLParserFailedException ( const location &location, const std::string &msg ) :
  runtime_error ( join ( location, msg ) ) {

}

SQLParserFailedException::SQLParserFailedException ( const location &location, const char *msg ) :
  runtime_error ( join ( location, msg ) ) {

}
