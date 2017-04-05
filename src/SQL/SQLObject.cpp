//
// Created by David van Laatum on 26/3/17.
//

#include "SQLObject.h"

std::ostream &operator<< ( std::ostream &os, const SQLObject &statement ) {
  os << statement.toString ();
  return os;
}

SQLObject::~SQLObject () {

}

std::ostream &operator<< ( std::ostream &os, const SQLObject *statement ) {
  if ( statement ) {
    os << statement->toString ();
  } else {
    os << "(null statement)";
  }
  return os;
}

std::string SQLObject::toString ( const SQLObject *const object ) {
  return object ? object->toString () : "(null)";
}
