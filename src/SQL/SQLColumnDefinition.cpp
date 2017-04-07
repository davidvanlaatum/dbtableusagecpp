//
// Created by David van Laatum on 7/4/17.
//

#include "SQLDataType.h"
#include "SQLColumnAttributes.h"
#include "SQLColumnDefinition.h"

SQLColumnDefinition::SQLColumnDefinition ( SQLIdentifier *name, SQLDataType *type, SQLColumnAttributes *attributes )
  : name ( name ), type ( type ), attributes ( attributes ) {
}

SQLColumnDefinition::~SQLColumnDefinition () {

}

std::string SQLColumnDefinition::toString () const {
  return "BLA";// TODO
}

void SQLColumnDefinition::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLColumnDefinition::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLObject *SQLColumnDefinition::clone () const {
  return new SQLColumnDefinition ( NULL, NULL, NULL );// TODO
}
