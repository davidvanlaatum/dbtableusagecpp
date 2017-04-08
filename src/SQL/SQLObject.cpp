//
// Created by David van Laatum on 26/3/17.
//

#include "SQLObject.h"

std::ostream &SQL::operator<< ( std::ostream &os, const SQL::SQLObject &statement ) {
  os << statement.toString ();
  return os;
}

SQL::SQLObject::~SQLObject () {

}

std::ostream &SQL::operator<< ( std::ostream &os, const SQL::SQLObject *statement ) {
  if ( statement ) {
    os << statement->toString ();
  } else {
    os << "(null statement)";
  }
  return os;
}

std::string SQL::SQLObject::toString ( const SQL::SQLObject *const object ) {
  return object ? object->toString () : "(null)";
}
