//
// Created by David van Laatum on 1/4/17.
//

#include "SQLReplaceIntoStatement.h"
#include "SQLTable.h"
#include "SQLObjectList.h"

SQL::SQLReplaceIntoStatement::SQLReplaceIntoStatement ( SQLTable *table, SQLObjectList<> *values ) : table ( table ),
                                                                                                values ( values ) {
}

std::string SQL::SQLReplaceIntoStatement::toString () const {
  return "REPLACE INTO " + SQLObject::toString ( table ) + " " + SQLObject::toString ( values );
}

SQL::SQLTable *SQL::SQLReplaceIntoStatement::getTable () const {
  return table.get ();
}

void SQL::SQLReplaceIntoStatement::getTables ( table_type &rt ) const {
  rt[table] = WRITE;
}

void SQL::SQLReplaceIntoStatement::resolve ( SQLParserContext *context ) {
  if ( table ) {
    table->resolve ( context );
  }
  values->resolve ( context );
}

void SQL::SQLReplaceIntoStatement::walk ( SQLTreeWalker *walker ) {
  if ( table ) {
    walker->walk ( table.get () );
  }
  walker->walk ( values.get () );
}

SQL::SQLReplaceIntoStatement *SQL::SQLReplaceIntoStatement::clone () const {
  return new SQLReplaceIntoStatement ( table ? table->clone () : NULL, values ? values->clone () : NULL );
}

size_t SQL::SQLReplaceIntoStatement::showAtVerboseLevel () const {
  return 1;
}
