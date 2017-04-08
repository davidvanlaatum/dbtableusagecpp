//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SETSTATEMENT_H
#define DBTABLEUSAGECPP_SETSTATEMENT_H

#include <boost/shared_ptr.hpp>
#include "SQLStatement.h"
#include "SQLSetPair.h"
#include "SQLObjectList.h"
class SQLSetStatement : public SQLStatement {
public:
    typedef SQLObjectList<SQLSetPair> ArgsType;
    SQLSetStatement ( SQLObjectList<> *args );
    SQLSetStatement ();
    virtual ~SQLSetStatement ();
    virtual std::string toString () const;
    const ArgsType &getArgs () const;
    virtual void getTables ( table_type &rt ) const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLSetStatement *clone () const;
    virtual size_t showAtVerboseLevel () const;
private:
    ArgsType args;
};

#ifdef GMOCK
class MockSQLSetStatement : public SQLSetStatement {
public:
  MOCK_METHOD2(statement, void(SQLStatement *statement, SQLParserContext *context));
};
#endif

#endif //DBTABLEUSAGECPP_SETSTATEMENT_H
