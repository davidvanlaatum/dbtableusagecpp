//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_USEDATABASE_H
#define DBTABLEUSAGECPP_USEDATABASE_H


#include "SQLStatement.h"
#include "SQLIdentifier.h"
class SQLUseDatabase : public SQLStatement {
public:
    virtual std::string toString () const;
    SQLUseDatabase ( SQLIdentifier *name );
    virtual void getTables ( table_type &rt ) const;
    virtual void resolve ( SQLParserContext *context );

    boost::shared_ptr<SQLIdentifier> getName () {
      return name;
    }

    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLUseDatabase *clone() const;
private:
    boost::shared_ptr<SQLIdentifier> name;
};


#endif //DBTABLEUSAGECPP_USEDATABASE_H
