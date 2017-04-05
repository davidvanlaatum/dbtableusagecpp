//
// Created by David van Laatum on 5/4/17.
//

#include "SQLCreateTableStatement.h"

SQLCreateTableStatement::SQLCreateTableStatement ( SQLTable *table, SQLObjectList<> *columns ) : table ( table ) {
}

SQLCreateTableStatement::~SQLCreateTableStatement () {

}

void SQLCreateTableStatement::getTables ( SQLStatement::table_type &rt ) const {

}

std::string SQLCreateTableStatement::toString () const {
  return "CREATE TABLE ";
}

void SQLCreateTableStatement::resolve ( SQLParserContext *context ) {

}

void SQLCreateTableStatement::walk ( SQLTreeWalker *walker ) {

}

SQLObject *SQLCreateTableStatement::clone () const {
  return NULL;
}
