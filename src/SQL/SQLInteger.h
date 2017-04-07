//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLINTEGER_H
#define DBTABLEUSAGECPP_SQLINTEGER_H

#include <stdint.h>
#include "SQLObject.h"
class SQLInteger : public SQLObject {
public:
    EMPTY_CONSTRUCTOR(SQLInteger)
    SQLInteger ( int64_t value );
    virtual std::string toString () const;
    int64_t toInt () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLInteger *clone () const;
    bool operator== ( int64_t rhs ) const;
private:
    int64_t value;
};


#endif //DBTABLEUSAGECPP_SQLINTEGER_H
