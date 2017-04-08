//
// Created by David van Laatum on 7/4/17.
//

#include "SQLAlterTableStatement.h"

SQL::SQLAlterTableStatement::SQLAlterTableStatement ( SQLTable *table, SQLObjectList<> *opts ) : table ( table ) {
  if (opts) {
    for ( SQLObjectList<>::iterator it = opts->begin (); it != opts->end (); ++it ) {
      operations.push ( *it );
    }
    opts->clear ();
  }
}

SQL::SQLAlterTableStatement::~SQLAlterTableStatement () {

}

std::string SQL::SQLAlterTableStatement::toString () const {
  return "ALTER TABLE " + operations.toString ();
}

void SQL::SQLAlterTableStatement::resolve ( SQLParserContext *context ) {
  if ( table ) {
    table->resolve ( context );
  }
}

void SQL::SQLAlterTableStatement::walk ( SQLTreeWalker *walker ) {
  if ( table ) {
    walker->walk ( table.get () );
  }
}

SQL::SQLAlterTableStatement *SQL::SQLAlterTableStatement::clone () const {
  SQLAlterTableStatement *statement = new SQLAlterTableStatement ( NULL, NULL );
  statement->table = table;
  return statement;
}

void SQL::SQLAlterTableStatement::getTables ( SQLStatement::table_type &rt ) const {
  if ( table ) {
    rt[table] = ALTER;
  }
}

size_t SQL::SQLAlterTableStatement::showAtVerboseLevel () const {
  return 1;
}
