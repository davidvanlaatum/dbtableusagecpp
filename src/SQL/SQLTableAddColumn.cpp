//
// Created by David van Laatum on 7/4/17.
//

#include "SQLColumnDefinition.h"
#include "SQLTableAddColumn.h"

SQL::SQLTableAddColumn::SQLTableAddColumn ( SQLColumnDefinition *p ) : definition ( p ) {
}

SQL::SQLTableAddColumn::~SQLTableAddColumn () {

}

std::string SQL::SQLTableAddColumn::toString () const {
  return "ADD COLUMN " + SQLObject::toString (definition);
}

void SQL::SQLTableAddColumn::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLTableAddColumn::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLTableAddColumn *SQL::SQLTableAddColumn::clone () const {
  SQLTableAddColumn *rt = new SQLTableAddColumn(NULL);
  rt->definition = definition;
  return rt;
}
