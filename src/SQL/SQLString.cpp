//
// Created by David van Laatum on 26/3/17.
//

#include "SQLString.h"

std::string SQL::SQLString::toString () const {
  return "'" + value + "'";
}

SQL::SQLString::SQLString ( const std::string &value ) {
  if ( !value.empty () && ( ( value.at ( 0 ) == '\'' && *( --value.end () ) == '\'' ) ||
                            ( value.at ( 0 ) == '"' && *( --value.end () ) == '"' ) ) ) {
    this->value = value.substr ( 1, value.size () - 2 );
  } else {
    this->value = value;
  }
}

void SQL::SQLString::resolve ( SQLParserContext *context ) {

}

void SQL::SQLString::walk ( SQLTreeWalker *walker ) {

}

SQL::SQLString *SQL::SQLString::clone () const {
  return new SQLString ( value );
}
