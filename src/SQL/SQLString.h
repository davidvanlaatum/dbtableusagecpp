//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLSTRING_H
#define DBTABLEUSAGECPP_SQLSTRING_H

#include "SQLObject.h"
class SQLString : public SQLObject {
public:
    SQLString ( const std::string &value );
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLString *clone () const;
private:
    std::string value;
};


#endif //DBTABLEUSAGECPP_SQLSTRING_H
