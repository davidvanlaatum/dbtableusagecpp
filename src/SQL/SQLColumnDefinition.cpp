//
// Created by David van Laatum on 7/4/17.
//

#include "SQLDataType.h"
#include "SQLColumnAttributes.h"
#include "SQLColumnDefinition.h"

SQL::SQLColumnDefinition::SQLColumnDefinition ( SQLIdentifier *name, SQLDataType *type, SQLColumnAttributes *attributes )
  : name ( name ), type ( type ), attributes ( attributes ) {
}

SQL::SQLColumnDefinition::~SQLColumnDefinition () {

}

std::string SQL::SQLColumnDefinition::toString () const {
  return SQLObject::toString ( name ) + " " + SQLObject::toString ( type ) + " " + SQLObject::toString ( attributes );
}

void SQL::SQLColumnDefinition::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLColumnDefinition::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLColumnDefinition *SQL::SQLColumnDefinition::clone () const {
  return new SQLColumnDefinition ( NULL, NULL, NULL );// TODO
}
