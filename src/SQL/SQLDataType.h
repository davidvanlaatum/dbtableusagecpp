//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLDATATYPE_H
#define DBTABLEUSAGECPP_SQLDATATYPE_H

#include "SQLObject.h"
#include "sql-parser.hpp"

class SQLDataLength;
class SQLDataCollation;

typedef yy::SQLParser::token::yytokentype datatype;
class SQLDataType : public SQLObject {
public:
    EMPTY_CONSTRUCTOR(SQLDataType)
    SQLDataType ( datatype type );
    SQLDataType ( datatype type, SQLDataLength *length );
    SQLDataType ( datatype type, SQLDataLength *length, int flag );
    SQLDataType ( datatype type, SQLDataLength *length, SQLDataCollation *collation );
    SQLDataType ( datatype type, SQLDataCollation *length, int flag );
    SQLDataType ( datatype type, SQLObjectList<> *opts, SQLDataCollation *collation );
    virtual ~SQLDataType ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLDataType * clone () const;
private:
    datatype type;
    boost::shared_ptr<SQLDataLength> length;
    boost::shared_ptr<SQLDataCollation> collation;
};

class SQLDataLength : public SQLObject {
public:
    EMPTY_CONSTRUCTOR(SQLDataLength)
    SQLDataLength ( int length );
    SQLDataLength ( int length, int );
    virtual ~SQLDataLength ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLDataLength * clone () const;
private:
    int length;
};

class SQLDataCollation : public SQLObject {
public:
    EMPTY_CONSTRUCTOR(SQLDataCollation)
    SQLDataCollation ( char *name );
    virtual ~SQLDataCollation ();
    virtual std::string toString () const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLDataCollation * clone () const;
private:
    std::string name;
};

#endif //DBTABLEUSAGECPP_SQLDATATYPE_H
