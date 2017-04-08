//
// Created by David van Laatum on 7/4/17.
//

#include "SQLColumnAttributes.h"

SQL::SQLColumnAttributes::SQLColumnAttributes () {
  isNull = true;
}

SQL::SQLColumnAttributes::~SQLColumnAttributes () {

}

std::string SQL::SQLColumnAttributes::toString () const {
  return "COLUMN ATTRIBUTES"; // TODO
}

void SQL::SQLColumnAttributes::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLColumnAttributes::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLColumnAttributes *SQL::SQLColumnAttributes::clone () const {
  return new SQLColumnAttributes (); // TODO
}

void SQL::SQLColumnAttributes::notNull () {
  isNull = false;
}

void SQL::SQLColumnAttributes::null () {
  isNull = true;
}

void SQL::SQLColumnAttributes::addDefault ( char *value ) {
  defaultString = value;
}

void SQL::SQLColumnAttributes::addDefault ( int value ) {
  defaultInt = value;
}

void SQL::SQLColumnAttributes::addDefault ( double value ) {
  defaultDouble = value;
}

void SQL::SQLColumnAttributes::addDefault ( bool value ) {
  defaultBool = value;
}

void SQL::SQLColumnAttributes::autoIncrement () {
  isAutoIncrement = true;
}

void SQL::SQLColumnAttributes::addComment ( char *value ) {
  comment = value;
}
