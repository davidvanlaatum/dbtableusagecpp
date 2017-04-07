//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLALTERTABLE_H
#define DBTABLEUSAGECPP_SQLALTERTABLE_H

#include "SQLStatement.h"
#include "SQLObjectList.h"

class SQLAlterTableStatement : public SQLStatement {
public:
    SQLAlterTableStatement ( SQLTable *table, SQLObjectList<> *opts );
    virtual ~SQLAlterTableStatement ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLObject *clone () const;
    virtual void getTables ( table_type &rt ) const;

private:
    boost::shared_ptr<SQLTable> table;
    SQLObjectList<> operations;
};

class SQLAlterTableColumnOperation : public SQLObject {

};


#endif //DBTABLEUSAGECPP_SQLALTERTABLE_H
