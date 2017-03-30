//
// Created by David van Laatum on 26/3/17.
//

#include <stdio.h>
#include "SQLInteger.h"

std::string SQLInteger::toString () const {
  char buffer[32];
  sprintf ( buffer, "%lld", value );

  return std::string ( buffer );
}

SQLInteger::SQLInteger ( int64_t value ) : value ( value ) {
}

int64_t SQLInteger::toInt () const {
  return value;
}
