//
// Created by David van Laatum on 7/4/17.
//

#include "SQLColumnDefinition.h"
#include "SQLTableAddColumn.h"

SQLTableAddColumn::SQLTableAddColumn ( SQLColumnDefinition *p ) : definition ( p ) {
}

SQLTableAddColumn::~SQLTableAddColumn () {

}

std::string SQLTableAddColumn::toString () const {
  return "ADD COLUMN " + definition->toString ();
}

void SQLTableAddColumn::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLTableAddColumn::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLObject *SQLTableAddColumn::clone () const {
  SQLTableAddColumn *rt = new SQLTableAddColumn(NULL);
  rt->definition = definition;
  return rt;
}
