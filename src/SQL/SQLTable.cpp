//

#include "SQLTable.h"
#include "SQLParserContext.h"

SQL::SQLTable::SQLTable ( SQLIdentifier *schema, SQLIdentifier *name ) : schema ( schema ), name ( name ) {

}

SQL::SQLTable::SQLTable ( SQLIdentifier *name ) : name ( name ) {

}

SQL::SQLTable::SQLTable ( const SQLTable &table ) {
  if ( table.schema ) {
    schema = boost::shared_ptr<SQLIdentifier> ( table.schema->clone () );
  }
  if ( table.name ) {
    name = boost::shared_ptr<SQLIdentifier> ( table.name->clone () );
  }
}

std::string SQL::SQLTable::toString () const {
  if ( schema == NULL ) {
    return SQL::SQLObject::toString ( name );
  } else {
    return SQLObject::toString ( schema ) + "." + SQLObject::toString ( name );
  }
}

void SQL::SQLTable::resolve ( SQLParserContext *context ) {
  if ( !schema ) {
    schema = context->getCurrentDatabase ();
  }
}

void SQL::SQLTable::walk ( SQLTreeWalker *walker ) {
  if ( schema ) {
    walker->walk ( schema.get () );
  }
  if ( name ) {
    walker->walk ( name.get () );
  }
}

SQL::SQLTable *SQL::SQLTable::clone () const {
  return new SQLTable ( schema ? schema->clone () : NULL, name ? name->clone () : NULL );
}
