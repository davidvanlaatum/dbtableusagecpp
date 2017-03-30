//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLINTEGER_H
#define DBTABLEUSAGECPP_SQLINTEGER_H

#include "SQLObject.h"
class SQLInteger : public SQLObject {
public:
    std::string toString () const override;
    int64_t toInt() const;

private:
    int64_t value;
public:
    SQLInteger ( int64_t value );
};


#endif //DBTABLEUSAGECPP_SQLINTEGER_H
