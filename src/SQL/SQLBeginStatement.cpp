//
// Created by David van Laatum on 5/4/17.
//

#include "SQLBeginStatement.h"

SQLBeginStatement::SQLBeginStatement () {
}

SQLBeginStatement::~SQLBeginStatement () {

}

std::string SQLBeginStatement::toString () const {
  return "BEGIN";
}

void SQLBeginStatement::resolve ( SQLParserContext *context ) {

}

void SQLBeginStatement::walk ( SQLTreeWalker *walker ) {

}

SQLObject *SQLBeginStatement::clone () const {
  return new SQLBeginStatement ();
}

void SQLBeginStatement::getTables ( SQLStatement::table_type &rt ) const {

}
