//
// Created by David van Laatum on 27/3/17.
//

#include "SQLDeleteStatement.h"

SQL::SQLDeleteStatement::SQLDeleteStatement ( SQLTable *table, SQLObject *where ) : table ( table ),
                                                                               where ( where ) {
}

std::string SQL::SQLDeleteStatement::toString () const {
  return "DELETE FROM " + SQLObject::toString ( table ) + " " +
         ( !where ? "" : "WHERE " + SQLObject::toString ( where ) );
}

void SQL::SQLDeleteStatement::getTables ( table_type &rt ) const {
  rt[table] = WRITE;
}

void SQL::SQLDeleteStatement::resolve ( SQLParserContext *context ) {
  if ( table ) {
    table->resolve ( context );
  }
  if ( where ) {
    where->resolve ( context );
  }
}

void SQL::SQLDeleteStatement::walk ( SQLTreeWalker *walker ) {
  if ( table ) {
    walker->walk ( table.get () );
  }
  if ( where ) {
    walker->walk ( where.get () );
  }
}

SQL::SQLDeleteStatement *SQL::SQLDeleteStatement::clone () const {
  return new SQLDeleteStatement ( table ? table->clone () : NULL, where ? where->clone () : NULL );
}

size_t SQL::SQLDeleteStatement::showAtVerboseLevel () const {
  return 1;
}
