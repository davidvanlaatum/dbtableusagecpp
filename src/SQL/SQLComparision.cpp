//
// Created by David van Laatum on 2/4/17.
//
#include "SQLComparision.h"
#include "SQLEquals.h"

SQL::SQLComparision::SQLComparision ( SQLObject *left, SQLObject *right ) : left ( left ), right ( right ) {

}

SQL::SQLComparision *SQL::SQLComparision::construct ( SQLComparisionType type, SQLObject *left, SQLObject *right ) {
  SQLComparision *rt = NULL;
  switch ( type ) {
    case EQUALTO:
      rt = new SQLEquals ( left, right );
      break;
    case LESSTHAN:
      break;
    case GREATERTHAN:
      break;
    case NOTEQUALTO:
      break;
    case LESSTHAN_OR_EQUALTO:
      break;
    case GREATERTHAN_OR_EQUALTO:
      break;
    case NULL_EQUALS:
      break;
  }
  return rt;
}

void SQL::SQLComparision::resolve ( SQLParserContext *context ) {
  if ( left ) {
    left->resolve ( context );
  }
  if ( right ) {
    right->resolve ( context );
  }
}

void SQL::SQLComparision::walk ( SQLTreeWalker *walker ) {
  if ( left ) {
    walker->walk ( left.get () );
  }
  if ( right ) {
    walker->walk ( right.get () );
  }
}

