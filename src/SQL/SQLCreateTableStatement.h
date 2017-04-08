//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCREATETABLESTATEMENT_H
#define DBTABLEUSAGECPP_SQLCREATETABLESTATEMENT_H

#include "SQLStatement.h"
#include "SQLObjectList.h"

class SQLCreateTableStatement : public SQLStatement {
public:
    EMPTY_CONSTRUCTOR(SQLCreateTableStatement)
    SQLCreateTableStatement ( bool temporary, bool notExists, SQLTable *table, SQLObjectList<> *columns );
    virtual ~SQLCreateTableStatement ();
    virtual void getTables ( table_type &rt ) const;
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLCreateTableStatement * clone () const;
    virtual size_t showAtVerboseLevel () const;
private:
    bool temporary;
    bool notExists;
    boost::shared_ptr<SQLTable> table;
    SQLObjectList<> columns;
};


#endif //DBTABLEUSAGECPP_SQLCREATETABLESTATEMENT_H
