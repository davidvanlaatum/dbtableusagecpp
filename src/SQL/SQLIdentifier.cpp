//
// Created by David van Laatum on 1/4/17.
//

#include "SQLIdentifier.h"

SQLIdentifier::SQLIdentifier () {
}

SQLIdentifier::SQLIdentifier ( const std::string &id ) {
  if ( id.empty () ) {
  } else if ( id.at ( 0 ) == '`' || id.at ( 0 ) == '"' ) {
    this->id = id.substr ( 1, id.size () - 2 );
  } else {
    this->id = id;
  }
}

std::string SQLIdentifier::toString () const {
  return "`" + id + "`";
}

SQLIdentifier::operator std::string () const {
  return id;
}

void SQLIdentifier::resolve ( SQLParserContext *context ) {

}

void SQLIdentifier::walk ( SQLTreeWalker *walker ) {

}

SQLIdentifier *SQLIdentifier::clone () const {
  return new SQLIdentifier ( id );
}
