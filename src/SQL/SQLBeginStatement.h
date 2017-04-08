//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLBEGINSTATEMENT_H
#define DBTABLEUSAGECPP_SQLBEGINSTATEMENT_H

#include "SQLStatement.h"

class SQLBeginStatement : public SQLStatement {
public:
    SQLBeginStatement ();
    virtual ~SQLBeginStatement ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLBeginStatement *clone () const;
    virtual void getTables ( table_type &rt ) const;
    virtual size_t showAtVerboseLevel () const;
};


#endif //DBTABLEUSAGECPP_SQLBEGINSTATEMENT_H
