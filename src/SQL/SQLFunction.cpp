//
// Created by David van Laatum on 1/4/17.
//
#include <boost/algorithm/string.hpp>
#include "SQLFunction.h"

SQL::SQLFunction::SQLFunction ( SQLIdentifier *identifier, SQLObjectList<> *args ) : name ( identifier ), args ( args ) {

}

std::string SQL::SQLFunction::toString () const {
  return SQL::SQLObject::toString ( name ) + SQLObject::toString ( args );
}

void SQL::SQLFunction::resolve ( SQLParserContext *context ) {
  args->resolve ( context );
}

void SQL::SQLFunction::walk ( SQLTreeWalker *walker ) {
  if ( name ) {
    walker->walk ( name.get () );
  }
  walker->walk ( args.get () );
}

SQL::SQLFunction *SQL::SQLFunction::clone () const {
  return new SQLFunction ( name ? name->clone () : NULL, args ? args->clone () : NULL );
}
