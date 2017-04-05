//
// Created by David van Laatum on 1/4/17.
//

#include "SQLColumn.h"

SQLColumn::SQLColumn ( SQLTable *table, SQLIdentifier *name ) : table ( table ), name ( name ) {
}

SQLColumn::SQLColumn ( SQLIdentifier *name ) : name ( name ) {
}

std::string SQLColumn::toString () const {
  if ( !table ) {
    return SQLObject::toString ( name );
  } else {
    return SQLObject::toString ( table ) + "." + SQLObject::toString ( name );
  }
}

void SQLColumn::resolve ( SQLParserContext *context ) {
  if ( table != NULL ) {
    table->resolve ( context );
  }
}

void SQLColumn::walk ( SQLTreeWalker *walker ) {
  if ( table != NULL ) {
    walker->walk ( table.get () );
  }
}

SQLColumn *SQLColumn::clone () const {
  return new SQLColumn ( table ? table->clone () : NULL, name ? name->clone () : NULL );
}
