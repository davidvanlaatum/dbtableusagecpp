//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCREATEDATABASESTATEMENT_H
#define DBTABLEUSAGECPP_SQLCREATEDATABASESTATEMENT_H
#include "SQLStatement.h"

class SQLCreateDatabaseStatement : public SQLStatement {
public:
    SQLCreateDatabaseStatement ( SQLIdentifier *name );
    virtual ~SQLCreateDatabaseStatement ();
    virtual void getTables ( table_type &rt ) const;
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLObject *clone () const;

private:
    boost::shared_ptr<SQLIdentifier> name;
};


#endif //DBTABLEUSAGECPP_SQLCREATEDATABASESTATEMENT_H
