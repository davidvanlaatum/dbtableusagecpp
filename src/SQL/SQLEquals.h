//
// Created by David van Laatum on 2/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLEQUALS_H
#define DBTABLEUSAGECPP_SQLEQUALS_H

#include "SQLComparision.h"
namespace SQL {
  class SQLEquals : public SQLComparision {
  public:
      EMPTY_CONSTRUCTOR( SQLEquals )
      SQLEquals ( SQLObject *left, SQLObject *right );
      virtual std::string toString () const;
      virtual SQLEquals *clone () const;
  };
}

#endif //DBTABLEUSAGECPP_SQLEQUALS_H
