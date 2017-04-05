//
// Created by David van Laatum on 5/4/17.
//

#include "SQLCommitStatement.h"

SQLCommitStatement::~SQLCommitStatement () {

}

std::string SQLCommitStatement::toString () const {
  return "COMMIT";
}

void SQLCommitStatement::resolve ( SQLParserContext *context ) {

}

void SQLCommitStatement::walk ( SQLTreeWalker *walker ) {

}

SQLCommitStatement *SQLCommitStatement::clone () const {
  return new SQLCommitStatement ();
}

void SQLCommitStatement::getTables ( SQLStatement::table_type &rt ) const {

}
