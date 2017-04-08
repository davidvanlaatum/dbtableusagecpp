//
// Created by David van Laatum on 26/3/17.
//

#include "SQLSetPair.h"
#include "SQLString.h"

std::string SQL::SQLSetPair::toString () const {
  return name + "=" + SQLObject::toString ( value );
}

SQL::SQLSetPair::SQLSetPair ( const std::string &name, SQLObject *value ) : name ( name ), value ( value ) {
}

SQL::SQLSetPair::~SQLSetPair () {
}

const std::string &SQL::SQLSetPair::getName () const {
  return name;
}

SQL::SQLObject *SQL::SQLSetPair::getValue () {
  return value.get ();
}

void SQL::SQLSetPair::resolve ( SQLParserContext *context ) {
  if ( value ) {
    value->resolve ( context );
  }
}

void SQL::SQLSetPair::walk ( SQLTreeWalker *walker ) {
  if ( value ) {
    walker->walk ( value.get () );
  }
}

SQL::SQLSetPair *SQL::SQLSetPair::clone () const {
  return new SQLSetPair ( name, value ? value->clone () : NULL );
}

