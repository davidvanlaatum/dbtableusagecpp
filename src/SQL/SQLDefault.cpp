//
// Created by David van Laatum on 26/3/17.
//

#include "SQLDefault.h"

std::string SQL::SQLDefault::toString () const {
  return "DEFAULT";
}

void SQL::SQLDefault::resolve ( SQLParserContext *context ) {

}

void SQL::SQLDefault::walk ( SQLTreeWalker *walker ) {

}

SQL::SQLDefault *SQL::SQLDefault::clone () const {
  return new SQLDefault ();
}
