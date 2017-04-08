//
// Created by David van Laatum on 7/4/17.
//

#include "SQLTableDropColumn.h"

SQL::SQLTableDropColumn::SQLTableDropColumn ( SQLColumn *column ) : column ( column ) {
}

SQL::SQLTableDropColumn::~SQLTableDropColumn () {

}

std::string SQL::SQLTableDropColumn::toString () const {
  return "DROP COLUMN " + SQLObject::toString ( column );
}

void SQL::SQLTableDropColumn::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLTableDropColumn::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLTableDropColumn *SQL::SQLTableDropColumn::clone () const {
  SQLTableDropColumn *rt = new SQLTableDropColumn(NULL);
  rt->column = column;
  return rt;
}
