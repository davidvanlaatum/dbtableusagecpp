//
// Created by David van Laatum on 5/4/17.
//

#include "SQLCommitStatement.h"

SQL::SQLCommitStatement::~SQLCommitStatement () {

}

std::string SQL::SQLCommitStatement::toString () const {
  return "COMMIT";
}

void SQL::SQLCommitStatement::resolve ( SQLParserContext *context ) {

}

void SQL::SQLCommitStatement::walk ( SQLTreeWalker *walker ) {

}

SQL::SQLCommitStatement *SQL::SQLCommitStatement::clone () const {
  return new SQLCommitStatement ();
}

void SQL::SQLCommitStatement::getTables ( SQLStatement::table_type &rt ) const {

}

size_t SQL::SQLCommitStatement::showAtVerboseLevel () const {
  return 2;
}
