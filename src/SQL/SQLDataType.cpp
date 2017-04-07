//
// Created by David van Laatum on 7/4/17.
//

#include "SQLDataType.h"

SQLDataType::SQLDataType ( yy::SQLParser::token::yytokentype type ) : type ( type ) {

}

SQLDataType::SQLDataType ( SQLDataType::datatype type, SQLDataLength *length ) : type ( type ), length ( length ) {

}

SQLDataType::SQLDataType ( SQLDataType::datatype type, SQLDataLength *length, int flag ) : type ( type ), length
  ( length ) {

}

SQLDataType::SQLDataType ( SQLDataType::datatype type, SQLDataLength *length, SQLDataCollation *collation ) :
  type ( type ), length ( length ), collation ( collation ) {

}

SQLDataType::SQLDataType ( SQLDataType::datatype type, SQLDataCollation *collation, int flag ) : type ( type ),
                                                                                                 collation (
                                                                                                   collation ) {

}

SQLDataType::SQLDataType ( SQLDataType::datatype type, SQLObjectList<> *opts, SQLDataCollation *collation ) :
  type ( type ), collation ( collation ) {

}

SQLDataType::~SQLDataType () {

}

std::string SQLDataType::toString () const {
  return "DATATYPE"; // TODO
}

void SQLDataType::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLDataType::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLObject *SQLDataType::clone () const {
  return new SQLDataType ( 0 );// TODO
}

SQLDataLength::SQLDataLength ( int length ) {
// TODO
}

SQLDataLength::SQLDataLength ( int length, int ) {
// TODO
}

SQLDataLength::~SQLDataLength () {

}

std::string SQLDataLength::toString () const {
  return "LENGTH";// TODO
}

void SQLDataLength::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLDataLength::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLObject *SQLDataLength::clone () const {
  return new SQLDataLength ( 0 );// TODO
}

SQLDataCollation::SQLDataCollation ( char *name ) : name ( name ) {
  free ( name );
}

SQLDataCollation::~SQLDataCollation () {

}

std::string SQLDataCollation::toString () const {
  return "Collation";// TODO
}

void SQLDataCollation::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLDataCollation::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLObject *SQLDataCollation::clone () const {
  return new SQLDataCollation ( NULL );// TODO
}
