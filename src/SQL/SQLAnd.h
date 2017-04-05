//
// Created by david on 2/04/17.
//

#ifndef DBTABLEUSAGECPP_SQLAND_H
#define DBTABLEUSAGECPP_SQLAND_H

#include <boost/scoped_ptr.hpp>
#include "SQLExpression.h"

class SQLAnd : public SQLExpression {
public:
    SQLAnd ( SQLObject *left, SQLObject *right );
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLAnd *clone() const;
private:
    boost::scoped_ptr<SQLObject> left;
    boost::scoped_ptr<SQLObject> right;
};


#endif //DBTABLEUSAGECPP_SQLAND_H
