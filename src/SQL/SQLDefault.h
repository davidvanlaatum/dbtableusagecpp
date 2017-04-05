//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLDEFAULT_H
#define DBTABLEUSAGECPP_SQLDEFAULT_H

#include "SQLObject.h"
class SQLDefault : public SQLObject {
public:
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLDefault *clone () const;
};


#endif //DBTABLEUSAGECPP_SQLDEFAULT_H
