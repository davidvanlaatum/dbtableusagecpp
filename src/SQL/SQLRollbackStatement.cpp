//
// Created by David van Laatum on 5/4/17.
//

#include "SQLRollbackStatement.h"

SQL::SQLRollbackStatement::~SQLRollbackStatement () {

}

std::string SQL::SQLRollbackStatement::toString () const {
  return "ROLLBACK";
}

void SQL::SQLRollbackStatement::resolve ( SQLParserContext *context ) {

}

void SQL::SQLRollbackStatement::walk ( SQLTreeWalker *walker ) {

}

SQL::SQLRollbackStatement *SQL::SQLRollbackStatement::clone () const {
  return new SQLRollbackStatement ();
}

void SQL::SQLRollbackStatement::getTables ( SQLStatement::table_type &rt ) const {

}

size_t SQL::SQLRollbackStatement::showAtVerboseLevel () const {
  return 2;
}
