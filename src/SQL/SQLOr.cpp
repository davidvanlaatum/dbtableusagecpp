//
// Created by david on 2/04/17.
//

#include "SQLOr.h"

SQL::SQLOr::SQLOr ( SQLObject *left, SQLObject *right ) : left ( left ), right ( right ) {

}

std::string SQL::SQLOr::toString () const {
  return "(" + SQLObject::toString ( left ) + " OR " + SQLObject::toString ( right ) + ")";
}

void SQL::SQLOr::resolve ( SQLParserContext *context ) {
  if ( left ) {
    left->resolve ( context );
  }
  if ( right ) {
    right->resolve ( context );
  }
}

void SQL::SQLOr::walk ( SQLTreeWalker *walker ) {
  if ( left ) {
    walker->walk ( left.get () );
  }
  if ( right ) {
    walker->walk ( right.get () );
  }
}

SQL::SQLOr *SQL::SQLOr::clone () const {
  return new SQLOr ( left ? left->clone () : NULL, right ? right->clone () : NULL );
}
