//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCOLUMNDEFINITION_H
#define DBTABLEUSAGECPP_SQLCOLUMNDEFINITION_H

#include "SQLObject.h"
#include "SQLIdentifier.h"
class SQLDataType;
class SQLColumnAttributes;

class SQLColumnDefinition : public SQLObject {
public:
    SQLColumnDefinition ( SQLIdentifier *name, SQLDataType *type, SQLColumnAttributes *attributes );
    virtual ~SQLColumnDefinition ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLObject *clone () const;
private:
    boost::shared_ptr<SQLIdentifier> name;
    boost::shared_ptr<SQLDataType> type;
    boost::shared_ptr<SQLColumnAttributes> attributes;
};


#endif //DBTABLEUSAGECPP_SQLCOLUMNDEFINITION_H
