//
// Created by David van Laatum on 2/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCOMPARISION_H
#define DBTABLEUSAGECPP_SQLCOMPARISION_H

#include "boost/scoped_ptr.hpp"
#include "SQLExpression.h"
namespace SQL {
  enum SQLComparisionType {
      LESSTHAN = 1,
      GREATERTHAN = 2,
      NOTEQUALTO = 3,
      EQUALTO = 4,
      LESSTHAN_OR_EQUALTO = 5,
      GREATERTHAN_OR_EQUALTO = 6,
      NULL_EQUALS = 12
  };

/*abstract*/ class SQLComparision : public SQLExpression {
  public:
      EMPTY_CONSTRUCTOR( SQLComparision )
      SQLComparision ( SQLObject *left, SQLObject *right );
/*
    inline const SQLObject *getLeft () const {
      return left.get ();
    }

    inline const SQLObject *getRight () const {
      return right.get ();
    }*/

      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      static SQLComparision *construct ( SQLComparisionType type, SQLObject *left, SQLObject *right );
  protected:
      boost::shared_ptr<SQLObject> left;
      boost::shared_ptr<SQLObject> right;
  };
}


#endif //DBTABLEUSAGECPP_SQLCOMPARISION_H
