//
// Created by David van Laatum on 26/3/17.
//

#include "SQLString.h"

std::string SQLString::toString () const {
  return "'" + value + "'";
}

SQLString::SQLString ( const std::string &value ) : value ( value ) {
}

void SQLString::resolve ( SQLParserContext *context ) {

}

void SQLString::walk ( SQLTreeWalker *walker ) {

}

SQLString *SQLString::clone () const {
  return new SQLString ( value );
}
