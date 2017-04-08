//
// Created by David van Laatum on 1/4/17.
//

#include "SQLColumn.h"

SQL::SQLColumn::SQLColumn ( SQLTable *table, SQLIdentifier *name ) : table ( table ), name ( name ) {
}

SQL::SQLColumn::SQLColumn ( SQLIdentifier *name ) : name ( name ) {
}

std::string SQL::SQLColumn::toString () const {
  if ( !table ) {
    return SQL::SQLObject::toString ( name );
  } else {
    return SQLObject::toString ( table ) + "." + SQLObject::toString ( name );
  }
}

void SQL::SQLColumn::resolve ( SQLParserContext *context ) {
  if ( table != NULL ) {
    table->resolve ( context );
  }
}

void SQL::SQLColumn::walk ( SQLTreeWalker *walker ) {
  if ( table != NULL ) {
    walker->walk ( table.get () );
  }
}

SQL::SQLColumn *SQL::SQLColumn::clone () const {
  return new SQLColumn ( table ? table->clone () : NULL, name ? name->clone () : NULL );
}
