//
// Created by David van Laatum on 7/4/17.
//

#include "SQLAlterTableStatement.h"

SQLAlterTableStatement::SQLAlterTableStatement ( SQLTable *table, SQLObjectList<> *opts ) : table ( table ) {
  for ( SQLObjectList<>::iterator it = opts->begin (); it != opts->end (); ++it ) {
    operations.push ( *it );
  }
  opts->clear ();
}

SQLAlterTableStatement::~SQLAlterTableStatement () {

}

std::string SQLAlterTableStatement::toString () const {
  return "ALTER TABLE " + operations.toString ();
}

void SQLAlterTableStatement::resolve ( SQLParserContext *context ) {
  if ( table ) {
    table->resolve ( context );
  }
}

void SQLAlterTableStatement::walk ( SQLTreeWalker *walker ) {
  if ( table ) {
    walker->walk ( table.get () );
  }
}

SQLObject *SQLAlterTableStatement::clone () const {
  SQLAlterTableStatement *statement = new SQLAlterTableStatement ( NULL, NULL );
  statement->table = table;
  return statement;
}

void SQLAlterTableStatement::getTables ( SQLStatement::table_type &rt ) const {
  if ( table ) {
    rt[table] = ALTER;
  }
}
