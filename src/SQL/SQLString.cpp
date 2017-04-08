//
// Created by David van Laatum on 26/3/17.
//

#include "SQLString.h"

std::string SQLString::toString () const {
  return "'" + value + "'";
}

SQLString::SQLString ( const std::string &value ) {
  if ( !value.empty () && ( ( value.at ( 0 ) == '\'' && *( --value.end () ) == '\'' ) ||
                            ( value.at ( 0 ) == '"' && *( --value.end () ) == '"' ) ) ) {
    this->value = value.substr ( 1, value.size () - 2 );
  } else {
    this->value = value;
  }
}

void SQLString::resolve ( SQLParserContext *context ) {

}

void SQLString::walk ( SQLTreeWalker *walker ) {

}

SQLString *SQLString::clone () const {
  return new SQLString ( value );
}
