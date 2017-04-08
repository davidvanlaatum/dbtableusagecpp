//
// Created by David van Laatum on 2/4/17.
//

#include "SQLEquals.h"

SQL::SQLEquals::SQLEquals ( SQLObject *left, SQLObject *right ) : SQLComparision ( left, right ) {
}

std::string SQL::SQLEquals::toString () const {
  return SQLObject::toString ( left ) + " = " + SQLObject::toString ( right );
}

SQL::SQLEquals *SQL::SQLEquals::clone () const {
  return new SQLEquals ( left ? left->clone () : NULL, right ? right->clone () : NULL );
}
