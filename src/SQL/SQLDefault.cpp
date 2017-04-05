//
// Created by David van Laatum on 26/3/17.
//

#include "SQLDefault.h"

std::string SQLDefault::toString () const {
  return "DEFAULT";
}

void SQLDefault::resolve ( SQLParserContext *context ) {

}

void SQLDefault::walk ( SQLTreeWalker *walker ) {

}

SQLDefault *SQLDefault::clone () const {
  return new SQLDefault ();
}
