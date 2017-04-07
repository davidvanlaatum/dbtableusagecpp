//
// Created by David van Laatum on 7/4/17.
//
#include "SQLColumnDefinition.h"
#include "SQLTableModifyColumn.h"

SQLTableModifyColumn::SQLTableModifyColumn ( SQLColumnDefinition *p ) : definition ( p ) {
}

SQLTableModifyColumn::~SQLTableModifyColumn () {

}

std::string SQLTableModifyColumn::toString () const {
  return "MODIFY COLUMN" + SQLObject::toString ( definition );
}

void SQLTableModifyColumn::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLTableModifyColumn::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLTableModifyColumn *SQLTableModifyColumn::clone () const {
  SQLTableModifyColumn *rt = new SQLTableModifyColumn ( NULL );
  rt->definition = definition;
  return rt;
}
