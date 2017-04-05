//
// Created by David van Laatum on 5/4/17.
//

#include "SQLRollbackStatement.h"

SQLRollbackStatement::~SQLRollbackStatement () {

}

std::string SQLRollbackStatement::toString () const {
  return "ROLLBACK";
}

void SQLRollbackStatement::resolve ( SQLParserContext *context ) {

}

void SQLRollbackStatement::walk ( SQLTreeWalker *walker ) {

}

SQLObject *SQLRollbackStatement::clone () const {
  return new SQLRollbackStatement();
}

void SQLRollbackStatement::getTables ( SQLStatement::table_type &rt ) const {

}
