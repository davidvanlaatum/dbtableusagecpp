//
// Created by David van Laatum on 29/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLPARSERCALLBACK_H
#define DBTABLEUSAGECPP_SQLPARSERCALLBACK_H

class SQLParserContext;
class SQLStatement;

class SQLParserCallback {
public:
    virtual void statement ( SQLStatement *statement, SQLParserContext *context ) = 0;
};

#ifdef GMOCK
class MockSQLParserCallback : public SQLParserCallback {
public:
  MOCK_METHOD2(statement, void(SQLStatement *statement, SQLParserContext *context));
};
#endif

#endif //DBTABLEUSAGECPP_SQLPARSERCALLBACK_H
