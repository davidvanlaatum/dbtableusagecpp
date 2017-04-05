//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLTABLE_H
#define DBTABLEUSAGECPP_SQLTABLE_H

#include <boost/scoped_ptr.hpp>
#include "SQLObject.h"
#include "SQLIdentifier.h"

class SQLTable : public SQLObject {
public:
    SQLTable ( SQLIdentifier *schema, SQLIdentifier *name );
    SQLTable ( SQLIdentifier *name );
    SQLTable ( const SQLTable &table );
    virtual std::string toString () const;
    virtual void walk ( SQLTreeWalker *walker );
    virtual void resolve ( SQLParserContext *context );

    const boost::shared_ptr<SQLIdentifier> &getSchema () const {
      return schema;
    }

    const boost::shared_ptr<SQLIdentifier> &getName () const {
      return name;
    }

    virtual SQLTable *clone () const;
private:
    boost::shared_ptr<SQLIdentifier> schema;
    boost::shared_ptr<SQLIdentifier> name;
};


#endif //DBTABLEUSAGECPP_SQLTABLE_H
