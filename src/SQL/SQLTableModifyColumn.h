//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLALTERTABLEMODIFYCOLUMN_H
#define DBTABLEUSAGECPP_SQLALTERTABLEMODIFYCOLUMN_H
#include "SQLAlterTableStatement.h"

class SQLColumnDefinition;
class SQLTableModifyColumn : public SQLAlterTableColumnOperation {
public:
    SQLTableModifyColumn (SQLColumnDefinition *p);
    virtual ~SQLTableModifyColumn ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLObject *clone () const;
private:
    boost::shared_ptr<SQLColumnDefinition> definition;
};


#endif //DBTABLEUSAGECPP_SQLALTERTABLEMODIFYCOLUMN_H
