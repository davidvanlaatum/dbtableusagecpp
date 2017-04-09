//
// Created by David van Laatum on 9/4/17.
//

#include <sstream>
#include "SQLDecimal.h"

SQL::SQLDecimal::SQLDecimal ( std::string value ) {
  char *end = NULL;
  fraction = 0;
  whole = strtol ( value.c_str (), &end, 0 );
  if ( end && end[0] == '.' ) {
    fraction = strtol ( end + 1, &end, 0 );
  }
}

SQL::SQLDecimal::SQLDecimal ( long whole, long fraction ) : whole ( whole ), fraction ( fraction ) {
}

SQL::SQLDecimal::~SQLDecimal () {

}

std::string SQL::SQLDecimal::toString () const {
  std::stringstream s;
  s << whole << "." << fraction;
  return s.str ();
}

void SQL::SQLDecimal::resolve ( SQL::SQLParserContext *context ) {

}

void SQL::SQLDecimal::walk ( SQL::SQLTreeWalker *walker ) {

}

SQL::SQLDecimal *SQL::SQLDecimal::clone () const {
  return new SQLDecimal(whole,fraction);
}

bool SQL::SQLDecimal::operator== ( const SQL::SQLObject &other ) const {
  const SQLDecimal *d;
  if ( ( d = dynamic_cast<const SQLDecimal *> ( &other ) ) != NULL ) {
    return d->whole == whole && d->fraction == fraction;
  }
  return false;
}

long SQL::SQLDecimal::getWhole () const {
  return whole;
}

long SQL::SQLDecimal::getFraction () const {
  return fraction;
}
