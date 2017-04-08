//
// Created by David van Laatum on 1/4/17.
//

#include "SQLReplaceIntoStatement.h"
#include "SQLTable.h"
#include "SQLObjectList.h"

SQLReplaceIntoStatement::SQLReplaceIntoStatement ( SQLTable *table, SQLObjectList<> *values ) : table ( table ),
                                                                                                values ( values ) {
}

std::string SQLReplaceIntoStatement::toString () const {
  return "REPLACE INTO " + SQLObject::toString ( table ) + " " + SQLObject::toString ( values );
}

SQLTable *SQLReplaceIntoStatement::getTable () const {
  return table.get ();
}

void SQLReplaceIntoStatement::getTables ( table_type &rt ) const {
  rt[table] = WRITE;
}

void SQLReplaceIntoStatement::resolve ( SQLParserContext *context ) {
  if ( table ) {
    table->resolve ( context );
  }
  values->resolve ( context );
}

void SQLReplaceIntoStatement::walk ( SQLTreeWalker *walker ) {
  if ( table ) {
    walker->walk ( table.get () );
  }
  walker->walk ( values.get () );
}

SQLReplaceIntoStatement *SQLReplaceIntoStatement::clone () const {
  return new SQLReplaceIntoStatement ( table ? table->clone () : NULL, values ? values->clone () : NULL );
}

size_t SQLReplaceIntoStatement::showAtVerboseLevel () const {
  return 1;
}
