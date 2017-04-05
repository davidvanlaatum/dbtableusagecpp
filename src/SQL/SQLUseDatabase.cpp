//
// Created by David van Laatum on 1/4/17.
//

#include "SQLUseDatabase.h"

SQLUseDatabase::SQLUseDatabase ( SQLIdentifier *name ) : name ( name ) {

}

std::string SQLUseDatabase::toString () const {
  return "Use " + SQLObject::toString ( name );
}

void SQLUseDatabase::getTables ( table_type &rt ) const {
}

void SQLUseDatabase::resolve ( SQLParserContext *context ) {

}

void SQLUseDatabase::walk ( SQLTreeWalker *walker ) {

}

SQLUseDatabase *SQLUseDatabase::clone () const {
  return new SQLUseDatabase ( name ? name->clone () : NULL );
}
