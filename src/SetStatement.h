//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SETSTATEMENT_H
#define DBTABLEUSAGECPP_SETSTATEMENT_H

#include "SQLStatement.h"
#include "SetPair.h"
#include "SQLObjectList.h"
class SetStatement : public SQLStatement {
public:
    SetStatement ( SQLObjectList<> *args );
    SetStatement ();
    virtual ~SetStatement ();
    std::string toString () const override;
    const SQLObjectList<SetPair *> &getArgs () const;
private:
    SQLObjectList<SetPair *> args;
};

#ifdef GMOCK
class MockSetStatement : public SetStatement {
public:
//  MOCK_METHOD2(statement, void(SQLStatement *statement, SQLParserContext *context));
};
#endif

#endif //DBTABLEUSAGECPP_SETSTATEMENT_H
