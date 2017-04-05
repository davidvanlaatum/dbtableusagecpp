//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCREATETABLESTATEMENT_H
#define DBTABLEUSAGECPP_SQLCREATETABLESTATEMENT_H

#include "SQLStatement.h"
#include "SQLObjectList.h"

class SQLCreateTableStatement : public SQLStatement {
public:
    SQLCreateTableStatement ( SQLTable *table, SQLObjectList<> *columns );
    virtual ~SQLCreateTableStatement ();
    virtual void getTables ( table_type &rt ) const;
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLObject *clone () const;
private:
    boost::shared_ptr<SQLTable> table;
};


#endif //DBTABLEUSAGECPP_SQLCREATETABLESTATEMENT_H
