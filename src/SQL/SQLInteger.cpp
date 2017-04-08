//
// Created by David van Laatum on 26/3/17.
//

#include <sstream>
#include "SQLInteger.h"

std::string SQL::SQLInteger::toString () const {
  std::stringstream buf;
  buf << value;
  return buf.str ();
}

SQL::SQLInteger::SQLInteger ( int64_t value ) : value ( value ) {
}

int64_t SQL::SQLInteger::toInt () const {
  return value;
}

void SQL::SQLInteger::resolve ( SQLParserContext *context ) {

}

void SQL::SQLInteger::walk ( SQLTreeWalker *walker ) {

}

bool SQL::SQLInteger::operator== ( int64_t rhs ) const {
  return value == rhs;
}

SQL::SQLInteger *SQL::SQLInteger::clone () const {
  return new SQLInteger ( value );
}
