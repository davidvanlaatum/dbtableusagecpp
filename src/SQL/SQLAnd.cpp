//
// Created by david on 2/04/17.
//

#include "SQLAnd.h"

SQLAnd::SQLAnd ( SQLObject *left, SQLObject *right ) : left ( left ), right ( right ) {

}

std::string SQLAnd::toString () const {
  return "(" + SQLObject::toString ( left ) + " AND " + SQLObject::toString ( right ) + ")";
}

void SQLAnd::resolve ( SQLParserContext *context ) {
  if ( left ) {
    left->resolve ( context );
  }
  if ( right ) {
    right->resolve ( context );
  }
}

void SQLAnd::walk ( SQLTreeWalker *walker ) {
  if ( left ) {
    walker->walk ( left.get () );
  }
  if ( right ) {
    walker->walk ( right.get () );
  }
}

SQLAnd *SQLAnd::clone () const {
  return new SQLAnd ( left ? left->clone () : NULL, right ? right->clone () : NULL );
}
