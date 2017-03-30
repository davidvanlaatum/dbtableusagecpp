//
// Created by David van Laatum on 26/3/17.
//

#include "SetPair.h"
#include "SQLString.h"

std::string SetPair::toString () const {
  return name + "=" + ( value ? value->toString () : "" );
}

SetPair::SetPair ( const std::string &name, SQLObject *value ) : name ( name ), value ( value ) {
}

SetPair::~SetPair () {
  if ( value ) {
    delete value;
    value = NULL;
  }
}

const std::string &SetPair::getName () const {
  return name;
}

SQLObject *SetPair::getValue () const {
  return value;
}

