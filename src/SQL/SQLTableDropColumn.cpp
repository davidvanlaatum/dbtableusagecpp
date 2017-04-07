//
// Created by David van Laatum on 7/4/17.
//

#include "SQLTableDropColumn.h"

SQLTableDropColumn::SQLTableDropColumn ( SQLColumn *column ) : column ( column ) {
}

SQLTableDropColumn::~SQLTableDropColumn () {

}

std::string SQLTableDropColumn::toString () const {
  return "DROP COLUMN " + SQLObject::toString ( column );
}

void SQLTableDropColumn::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLTableDropColumn::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLTableDropColumn *SQLTableDropColumn::clone () const {
  SQLTableDropColumn *rt = new SQLTableDropColumn(NULL);
  rt->column = column;
  return rt;
}
