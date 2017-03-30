//
// Created by David van Laatum on 27/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLDELETESTATEMENT_H
#define DBTABLEUSAGECPP_SQLDELETESTATEMENT_H

#include "SQLStatement.h"
#include "SQLExpression.h"

class SQLDeleteStatement : public SQLStatement {
public:
    SQLDeleteStatement ( const std::string &table, SQLExpression *where );
    virtual std::string toString () const;

private:
    std::string table;
    SQLExpression *where;
};


#endif //DBTABLEUSAGECPP_SQLDELETESTATEMENT_H
