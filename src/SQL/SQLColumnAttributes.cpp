//
// Created by David van Laatum on 7/4/17.
//

#include "SQLColumnAttributes.h"

SQLColumnAttributes::SQLColumnAttributes () {
  isNull = true;
}

SQLColumnAttributes::~SQLColumnAttributes () {

}

std::string SQLColumnAttributes::toString () const {
  return "COLUMN ATTRIBUTES"; // TODO
}

void SQLColumnAttributes::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLColumnAttributes::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLColumnAttributes *SQLColumnAttributes::clone () const {
  return new SQLColumnAttributes (); // TODO
}

void SQLColumnAttributes::notNull () {
  isNull = false;
}

void SQLColumnAttributes::null () {
  isNull = true;
}

void SQLColumnAttributes::addDefault ( char *value ) {
  defaultString = value;
}

void SQLColumnAttributes::addDefault ( int value ) {
  defaultInt = value;
}

void SQLColumnAttributes::addDefault ( double value ) {
  defaultDouble = value;
}

void SQLColumnAttributes::addDefault ( bool value ) {
  defaultBool = value;
}

void SQLColumnAttributes::autoIncrement () {
  isAutoIncrement = true;
}

void SQLColumnAttributes::addComment ( char *value ) {
  comment = value;
}
