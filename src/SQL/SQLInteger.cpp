//
// Created by David van Laatum on 26/3/17.
//

#include <sstream>
#include "SQLInteger.h"

std::string SQLInteger::toString () const {
  std::stringstream buf;
  buf << value;
  return buf.str ();
}

SQLInteger::SQLInteger ( int64_t value ) : value ( value ) {
}

int64_t SQLInteger::toInt () const {
  return value;
}

void SQLInteger::resolve ( SQLParserContext *context ) {

}

void SQLInteger::walk ( SQLTreeWalker *walker ) {

}

bool SQLInteger::operator== ( int64_t rhs ) const {
  return value == rhs;
}

SQLInteger *SQLInteger::clone () const {
  return new SQLInteger ( value );
}
