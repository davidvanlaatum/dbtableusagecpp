//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLIDENTIFIER_H
#define DBTABLEUSAGECPP_SQLIDENTIFIER_H

#include "SQLObject.h"
class SQLIdentifier : public SQLObject {
public:
    SQLIdentifier ();
    SQLIdentifier ( const std::string &id );
    virtual std::string toString () const;
    virtual operator std::string () const;
    virtual void resolve ( SQLParserContext *context );

    inline const std::string &getId () const {
      return id;
    }

    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLIdentifier *clone() const;
private:
    std::string id;
};


#endif //DBTABLEUSAGECPP_SQLIDENTIFIER_H
