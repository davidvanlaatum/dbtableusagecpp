//
// Created by David van Laatum on 1/4/17.
//

#include "SQLUseDatabase.h"

SQL::SQLUseDatabase::SQLUseDatabase ( SQLIdentifier *name ) : name ( name ) {

}

std::string SQL::SQLUseDatabase::toString () const {
  return "Use " + SQLObject::toString ( name );
}

void SQL::SQLUseDatabase::getTables ( table_type &rt ) const {
}

void SQL::SQLUseDatabase::resolve ( SQLParserContext *context ) {

}

void SQL::SQLUseDatabase::walk ( SQLTreeWalker *walker ) {

}

SQL::SQLUseDatabase *SQL::SQLUseDatabase::clone () const {
  return new SQLUseDatabase ( name ? name->clone () : NULL );
}

size_t SQL::SQLUseDatabase::showAtVerboseLevel () const {
  return 2;
}
