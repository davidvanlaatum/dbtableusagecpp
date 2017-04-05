//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCOMMITSTATEMENT_H
#define DBTABLEUSAGECPP_SQLCOMMITSTATEMENT_H

#include "SQLStatement.h"

class SQLCommitStatement : public SQLStatement {
public:
    virtual ~SQLCommitStatement ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLCommitStatement *clone () const;
    virtual void getTables ( table_type &rt ) const;
};


#endif //DBTABLEUSAGECPP_SQLCOMMITSTATEMENT_H
