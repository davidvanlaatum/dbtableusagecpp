//
// Created by David van Laatum on 2/4/17.
//

#include "SQLEquals.h"

SQLEquals::SQLEquals ( SQLObject *left, SQLObject *right ) : SQLComparision ( left, right ) {
}

std::string SQLEquals::toString () const {
  return SQLObject::toString ( left ) + " = " + SQLObject::toString ( right );
}

SQLEquals *SQLEquals::clone () const {
  return new SQLEquals ( left ? left->clone () : NULL, right ? right->clone () : NULL );
}
