//
// Created by David van Laatum on 26/3/17.
//

#include "SQLSetPair.h"
#include "SQLString.h"

std::string SQLSetPair::toString () const {
  return name + "=" + ( value ? SQLObject::toString ( value ) : "" );
}

SQLSetPair::SQLSetPair ( const std::string &name, SQLObject *value ) : name ( name ), value ( value ) {
}

SQLSetPair::~SQLSetPair () {
}

const std::string &SQLSetPair::getName () const {
  return name;
}

SQLObject *SQLSetPair::getValue () {
  return value.get ();
}

void SQLSetPair::resolve ( SQLParserContext *context ) {
  if ( value ) {
    value->resolve ( context );
  }
}

void SQLSetPair::walk ( SQLTreeWalker *walker ) {
  if ( value ) {
    walker->walk ( value.get () );
  }
}

SQLSetPair *SQLSetPair::clone () const {
  return new SQLSetPair ( name, value ? value->clone () : NULL );
}

