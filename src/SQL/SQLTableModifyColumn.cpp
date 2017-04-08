//
// Created by David van Laatum on 7/4/17.
//
#include "SQLColumnDefinition.h"
#include "SQLTableModifyColumn.h"

SQL::SQLTableModifyColumn::SQLTableModifyColumn ( SQLColumnDefinition *p ) : definition ( p ) {
}

SQL::SQLTableModifyColumn::~SQLTableModifyColumn () {

}

std::string SQL::SQLTableModifyColumn::toString () const {
  return "MODIFY COLUMN" + SQLObject::toString ( definition );
}

void SQL::SQLTableModifyColumn::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLTableModifyColumn::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLTableModifyColumn *SQL::SQLTableModifyColumn::clone () const {
  SQLTableModifyColumn *rt = new SQLTableModifyColumn ( NULL );
  rt->definition = definition;
  return rt;
}
