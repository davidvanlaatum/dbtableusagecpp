//
// Created by David van Laatum on 5/4/17.
//

#include "SQLCreateTableStatement.h"

SQLCreateTableStatement::SQLCreateTableStatement ( bool temporary, bool notExists, SQLTable *table,
                                                   SQLObjectList<> *columns ) : table ( table ), temporary ( temporary ),
                                                                                notExists ( notExists ) {
  if ( columns ) {
    for ( SQLObjectList<>::iterator it = columns->begin (); it != columns->end (); ++it ) {
      this->columns.push ( *it );
    }
    columns->clear ();
  }
}

SQLCreateTableStatement::~SQLCreateTableStatement () {

}

void SQLCreateTableStatement::getTables ( SQLStatement::table_type &rt ) const {
// TODO
}

std::string SQLCreateTableStatement::toString () const {
  return "CREATE TABLE ";// TODO
}

void SQLCreateTableStatement::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLCreateTableStatement::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLCreateTableStatement *SQLCreateTableStatement::clone () const {
  return new SQLCreateTableStatement(false,false,NULL,NULL);// TODO
}

size_t SQLCreateTableStatement::showAtVerboseLevel () const {
  return 1;
}
