//
// Created by David van Laatum on 1/4/17.
//

#include "SQLIdentifier.h"

SQL::SQLIdentifier::SQLIdentifier () {
}

SQL::SQLIdentifier::SQLIdentifier ( const std::string &id ) {
  if ( !id.empty () && ( ( id.at ( 0 ) == '`' && *( --id.end () ) == '`' ) ||
                         ( id.at ( 0 ) == '"' && *( --id.end () ) == '"' ) ) ) {
    this->id = id.substr ( 1, id.size () - 2 );
  } else {
    this->id = id;
  }
}

std::string SQL::SQLIdentifier::toString () const {
  return "`" + id + "`";
}

SQL::SQLIdentifier::operator std::string () const {
  return id;
}

void SQL::SQLIdentifier::resolve ( SQLParserContext *context ) {

}

void SQL::SQLIdentifier::walk ( SQLTreeWalker *walker ) {

}

SQL::SQLIdentifier *SQL::SQLIdentifier::clone () const {
  return new SQLIdentifier ( id );
}
