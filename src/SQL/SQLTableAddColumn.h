//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLTABLEADDCOLUMN_H
#define DBTABLEUSAGECPP_SQLTABLEADDCOLUMN_H
#include "SQLAlterTableStatement.h"

class SQLColumnDefinition;

class SQLTableAddColumn : public SQLAlterTableColumnOperation {
public:
    SQLTableAddColumn (SQLColumnDefinition *p);
    virtual ~SQLTableAddColumn ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLObject *clone () const;
private:
    boost::shared_ptr<SQLColumnDefinition> definition;
};


#endif //DBTABLEUSAGECPP_SQLTABLEADDCOLUMN_H
