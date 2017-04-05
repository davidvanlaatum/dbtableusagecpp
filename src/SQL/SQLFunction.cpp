//
// Created by David van Laatum on 1/4/17.
//
#include <boost/algorithm/string.hpp>
#include "SQLFunction.h"

SQLFunction::SQLFunction ( SQLIdentifier *identifier, SQLObjectList<> *args ) : name ( identifier ), args ( args ) {

}

std::string SQLFunction::toString () const {
  return SQLObject::toString ( name ) + SQLObject::toString ( args );
}

void SQLFunction::resolve ( SQLParserContext *context ) {
  args->resolve ( context );
}

void SQLFunction::walk ( SQLTreeWalker *walker ) {
  if ( name ) {
    walker->walk ( name.get () );
  }
  walker->walk ( args.get () );
}

SQLFunction *SQLFunction::clone () const {
  return new SQLFunction ( name ? name->clone () : NULL, args ? args->clone () : NULL );
}
