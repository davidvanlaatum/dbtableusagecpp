//
// Created by david on 2/04/17.
//

#include "SQLOr.h"

SQLOr::SQLOr ( SQLObject *left, SQLObject *right ) : left ( left ), right ( right ) {

}

std::string SQLOr::toString () const {
  return "(" + SQLObject::toString ( left ) + " OR " + SQLObject::toString ( right ) + ")";
}

void SQLOr::resolve ( SQLParserContext *context ) {
  if ( left ) {
    left->resolve ( context );
  }
  if ( right ) {
    right->resolve ( context );
  }
}

void SQLOr::walk ( SQLTreeWalker *walker ) {
  if ( left ) {
    walker->walk ( left.get () );
  }
  if ( right ) {
    walker->walk ( right.get () );
  }
}

SQLOr *SQLOr::clone () const {
  return new SQLOr ( left ? left->clone () : NULL, right ? right->clone () : NULL );
}
