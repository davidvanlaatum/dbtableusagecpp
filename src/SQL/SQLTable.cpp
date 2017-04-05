//

#include "SQLTable.h"
#include "SQLParserContext.h"

SQLTable::SQLTable ( SQLIdentifier *schema, SQLIdentifier *name ) : schema ( schema ), name ( name ) {

}

SQLTable::SQLTable ( SQLIdentifier *name ) : name ( name ) {

}

SQLTable::SQLTable ( const SQLTable &table ) {
  if ( table.schema ) {
    schema = boost::shared_ptr<SQLIdentifier> ( table.schema->clone () );
  }
  if ( table.name ) {
    name = boost::shared_ptr<SQLIdentifier> ( table.name->clone () );
  }
}

std::string SQLTable::toString () const {
  if ( schema == NULL ) {
    return SQLObject::toString ( name );
  } else {
    return SQLObject::toString ( schema ) + "." + SQLObject::toString ( name );
  }
}

void SQLTable::resolve ( SQLParserContext *context ) {
  if ( !schema ) {
    schema = context->getCurrentDatabase ();
  }
}

void SQLTable::walk ( SQLTreeWalker *walker ) {
  if ( schema ) {
    walker->walk ( schema.get () );
  }
  if ( name ) {
    walker->walk ( name.get () );
  }
}

SQLTable *SQLTable::clone () const {
  return new SQLTable ( schema ? schema->clone () : NULL, name ? name->clone () : NULL );
}
