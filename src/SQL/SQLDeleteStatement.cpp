//
// Created by David van Laatum on 27/3/17.
//

#include "SQLDeleteStatement.h"

SQLDeleteStatement::SQLDeleteStatement ( SQLTable *table, SQLObject *where ) : table ( table ),
                                                                               where ( where ) {
  assert ( table != where );
}

std::string SQLDeleteStatement::toString () const {
  return "DELETE FROM " + SQLObject::toString ( table ) + " " +
         ( !where ? "" : "WHERE " + SQLObject::toString ( where ) );
}

void SQLDeleteStatement::getTables ( table_type &rt ) const {
  rt[table] = WRITE;
}

void SQLDeleteStatement::resolve ( SQLParserContext *context ) {
  if ( table ) {
    table->resolve ( context );
  }
  if ( where ) {
    where->resolve ( context );
  }
}

void SQLDeleteStatement::walk ( SQLTreeWalker *walker ) {
  if ( table ) {
    walker->walk ( table.get () );
  }
  if ( where ) {
    walker->walk ( where.get () );
  }
}

SQLDeleteStatement *SQLDeleteStatement::clone () const {
  return new SQLDeleteStatement (table ? table->clone () : NULL, where ? where->clone () : NULL);
}
