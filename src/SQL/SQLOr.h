//
// Created by david on 2/04/17.
//

#ifndef DBTABLEUSAGECPP_SQLOR_H
#define DBTABLEUSAGECPP_SQLOR_H

#include <boost/scoped_ptr.hpp>
#include "SQLExpression.h"

class SQLOr : public SQLExpression {
public:
    SQLOr ( SQLObject *left, SQLObject *right );
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLOr *clone() const;
private:
    boost::scoped_ptr<SQLObject> left;
    boost::scoped_ptr<SQLObject> right;
};


#endif //DBTABLEUSAGECPP_SQLOR_H
