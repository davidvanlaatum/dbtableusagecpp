//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLTABLEDROPCOLUMN_H
#define DBTABLEUSAGECPP_SQLTABLEDROPCOLUMN_H
#include "SQLAlterTableStatement.h"
#include "SQLColumn.h"

class SQLTableDropColumn : public SQLAlterTableColumnOperation {
public:
    SQLTableDropColumn ( SQLColumn *column );
    virtual ~SQLTableDropColumn ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLObject *clone () const;
private:
    boost::shared_ptr<SQLColumn> column;
};


#endif //DBTABLEUSAGECPP_SQLTABLEDROPCOLUMN_H
