//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLDATATYPE_H
#define DBTABLEUSAGECPP_SQLDATATYPE_H

#include "SQLObject.h"
#include "sql-parser.hpp"
namespace SQL {
  class SQLDataLength;
  class SQLDataCollation;

  enum DataTypes {
      UNKNOWN,
      BIGINT,
      BINARY,
      BIT,
      BLOB,
      CHAR,
      DATE,
      DATETIME,
      DECIMAL,
      DOUBLE,
      ENUM,
      FLOAT,
      INTEGER,
      JSON,
      LONGBLOB,
      LONGTEXT,
      MEDIUMBLOB,
      MEDIUMINT,
      MEDIUMTEXT,
      REAL,
      SMALLINT,
      TEXT,
      TIME,
      TIMESTAMP,
      TINYBLOB,
      TINYINT,
      TINYTEXT,
      VARBINARY,
      VARCHAR,
      YEAR
  };

  typedef DataTypes datatype;
  class SQLDataType : public SQLObject {
  public:
      EMPTY_CONSTRUCTORI( SQLDataType, type(UNKNOWN) )
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
      virtual SQLDataType *clone () const;
  private:
      datatype type;
      boost::shared_ptr<SQLDataLength> length;
      boost::shared_ptr<SQLDataCollation> collation;
      static const char *typeStrings[];
  };

  class SQLDataLength : public SQLObject {
  public:
      EMPTY_CONSTRUCTOR( SQLDataLength )
      SQLDataLength ( int length );
      SQLDataLength ( int length, int );
      virtual ~SQLDataLength ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLDataLength *clone () const;
  private:
      int length;
  };

  class SQLDataCollation : public SQLObject {
  public:
      EMPTY_CONSTRUCTOR( SQLDataCollation )
      SQLDataCollation ( const char *name );
      virtual ~SQLDataCollation ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLDataCollation *clone () const;
  private:
      std::string name;
  };
}

#endif //DBTABLEUSAGECPP_SQLDATATYPE_H
