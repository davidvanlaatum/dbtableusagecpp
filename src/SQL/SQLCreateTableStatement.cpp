//
// Created by David van Laatum on 5/4/17.
//

#include "SQLCreateTableStatement.h"

SQL::SQLCreateTableStatement::SQLCreateTableStatement ( bool temporary, bool notExists, SQLTable *table,
                                                   SQLObjectList<> *columns, SQLObjectList<> *attributes ) :
  table ( table ), temporary ( temporary ), notExists ( notExists ) {
  if ( columns ) {
    for ( SQLObjectList<>::iterator it = columns->begin (); it != columns->end (); ++it ) {
      this->columns.push ( *it );
    }
    columns->clear ();
  }
}

SQL::SQLCreateTableStatement::~SQLCreateTableStatement () {

}

void SQL::SQLCreateTableStatement::getTables ( SQLStatement::table_type &rt ) const {
// TODO
}

std::string SQL::SQLCreateTableStatement::toString () const {
  return "CREATE TABLE " + columns.toString ();// TODO
}

void SQL::SQLCreateTableStatement::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLCreateTableStatement::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLCreateTableStatement *SQL::SQLCreateTableStatement::clone () const {
  return new SQLCreateTableStatement ( false, false, NULL, NULL, NULL );// TODO
}

size_t SQL::SQLCreateTableStatement::showAtVerboseLevel () const {
  return 1;
}
