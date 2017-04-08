//
// Created by David van Laatum on 7/4/17.
//

#include "SQLDataType.h"


const char *SQL::SQLDataType::typeStrings[] = {
  "BIGINT",
  "BINARY",
  "BIT",
  "BLOB",
  "CHAR",
  "DATE",
  "DATETIME",
  "DECIMAL",
  "DOUBLE",
  "ENUM",
  "FLOAT",
  "INTEGER",
  "JSON",
  "LONGBLOB",
  "LONGTEXT",
  "MEDIUMBLOB",
  "MEDIUMINT",
  "MEDIUMTEXT",
  "REAL",
  "SMALLINT",
  "TEXT",
  "TIME",
  "TIMESTAMP",
  "TINYBLOB",
  "TINYINT",
  "TINYTEXT",
  "VARBINARY",
  "VARCHAR",
  "YEAR",
};

SQL::SQLDataType::SQLDataType ( datatype type ) : type ( type ) {

}

SQL::SQLDataType::SQLDataType ( datatype type, SQLDataLength *length ) : type ( type ), length ( length ) {

}

SQL::SQLDataType::SQLDataType ( datatype type, SQLDataLength *length, int flag ) : type ( type ), length
  ( length ) {

}

SQL::SQLDataType::SQLDataType ( datatype type, SQLDataLength *length, SQLDataCollation *collation ) :
  type ( type ), length ( length ), collation ( collation ) {

}

SQL::SQLDataType::SQLDataType ( datatype type, SQLDataCollation *collation, int flag ) : type ( type ),
                                                                                                 collation (
                                                                                                   collation ) {

}

SQL::SQLDataType::SQLDataType ( datatype type, SQLObjectList<> *opts, SQLDataCollation *collation ) :
  type ( type ), collation ( collation ) {

}

SQL::SQLDataType::~SQLDataType () {

}

std::string SQL::SQLDataType::toString () const {
  return typeStrings[type]; // TODO
}

void SQL::SQLDataType::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLDataType::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLDataType *SQL::SQLDataType::clone () const {
  return new SQLDataType ( type );// TODO
}

SQL::SQLDataLength::SQLDataLength ( int length ) {
// TODO
}

SQL::SQLDataLength::SQLDataLength ( int length, int ) {
// TODO
}

SQL::SQLDataLength::~SQLDataLength () {

}

std::string SQL::SQLDataLength::toString () const {
  return "LENGTH";// TODO
}

void SQL::SQLDataLength::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLDataLength::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLDataLength *SQL::SQLDataLength::clone () const {
  return new SQLDataLength ( 0 );// TODO
}

SQL::SQLDataCollation::SQLDataCollation ( const char *name ) : name ( name ) {

}

SQL::SQLDataCollation::~SQLDataCollation () {

}

std::string SQL::SQLDataCollation::toString () const {
  return "Collation";// TODO
}

void SQL::SQLDataCollation::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLDataCollation::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLDataCollation *SQL::SQLDataCollation::clone () const {
  return new SQLDataCollation ( "" );// TODO
}
