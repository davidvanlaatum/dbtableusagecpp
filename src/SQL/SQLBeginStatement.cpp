//
// Created by David van Laatum on 5/4/17.
//

#include "SQLBeginStatement.h"

SQL::SQLBeginStatement::SQLBeginStatement () {
}

SQL::SQLBeginStatement::~SQLBeginStatement () {

}

std::string SQL::SQLBeginStatement::toString () const {
  return "BEGIN";
}

void SQL::SQLBeginStatement::resolve ( SQLParserContext *context ) {

}

void SQL::SQLBeginStatement::walk ( SQLTreeWalker *walker ) {

}

SQL::SQLBeginStatement *SQL::SQLBeginStatement::clone () const {
  return new SQLBeginStatement ();
}

void SQL::SQLBeginStatement::getTables ( SQLStatement::table_type &rt ) const {

}

size_t SQL::SQLBeginStatement::showAtVerboseLevel () const {
  return 2;
}
