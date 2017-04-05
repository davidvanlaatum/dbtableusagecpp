//
// Created by David van Laatum on 29/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLPARSERCALLBACK_H
#define DBTABLEUSAGECPP_SQLPARSERCALLBACK_H

#include <location.hh>

class SQLParserContext;
class SQLStatement;

typedef yy::location location;

class SQLParserCallback {
public:
    virtual void statement ( location &location, SQLStatement *statement, SQLParserContext *context ) = 0;
};

#ifdef GMOCK
class MockSQLParserCallback : public SQLParserCallback {
public:
    MOCK_METHOD3( statement, void(location &location, SQLStatement* statement, SQLParserContext* context) );
};
#endif

#endif //DBTABLEUSAGECPP_SQLPARSERCALLBACK_H
