//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLFUNCTION_H
#define DBTABLEUSAGECPP_SQLFUNCTION_H

#include "SQLExpression.h"
#include "SQLObjectList.h"
#include "SQLIdentifier.h"
#include <boost/scoped_ptr.hpp>
namespace SQL {
  class SQLFunction : public SQLExpression {
  public:
      EMPTY_CONSTRUCTOR( SQLFunction )
      SQLFunction ( SQLIdentifier *name, SQLObjectList<> *args );
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      static boost::shared_ptr<SQLObject> simplify ( SQLFunction *function );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLFunction *clone () const;
  private:
      boost::scoped_ptr<SQLIdentifier> name;
      boost::scoped_ptr<SQLObjectList<> > args;
  };
}

#endif //DBTABLEUSAGECPP_SQLFUNCTION_H
