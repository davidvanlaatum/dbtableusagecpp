//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLREPLACEINTO_H
#define DBTABLEUSAGECPP_SQLREPLACEINTO_H

#include "SQLObjectList.h"
#include "SQLStatement.h"
#include "SQLTable.h"

class SQLReplaceIntoStatement : public SQLStatement {
public:
    EMPTY_CONSTRUCTOR(SQLReplaceIntoStatement)
    SQLReplaceIntoStatement ( SQLTable *table, SQLObjectList<> *values );
    virtual std::string toString () const;
    virtual SQLTable *getTable () const;
    virtual void getTables ( table_type &rt ) const;
    virtual void resolve ( SQLParserContext *context );
    virtual SQLReplaceIntoStatement *clone () const;
    virtual void walk ( SQLTreeWalker *walker );
    virtual size_t showAtVerboseLevel () const;
private:
    boost::shared_ptr<SQLTable> table;
    boost::shared_ptr<SQLObjectList<> > values;
};


#endif //DBTABLEUSAGECPP_SQLREPLACEINTO_H
