//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCOLUMN_H
#define DBTABLEUSAGECPP_SQLCOLUMN_H

#include <boost/scoped_ptr.hpp>
#include "SQLObject.h"
#include "SQLTable.h"
#include "SQLIdentifier.h"

class SQLColumn : public SQLObject {
public:
    SQLColumn ( SQLTable *table, SQLIdentifier *name );
    SQLColumn ( SQLIdentifier *name );
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLColumn *clone () const;
private:
    boost::scoped_ptr<SQLTable> table;
    boost::scoped_ptr<SQLIdentifier> name;
};


#endif //DBTABLEUSAGECPP_SQLCOLUMN_H
