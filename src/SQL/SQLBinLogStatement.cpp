//
// Created by David van Laatum on 26/3/17.
//

#include <glib.h>
#include <iostream>
#include "SQLBinLogStatement.h"
#include "MySQLBinLogEvent.h"

SQLBinLogStatement::SQLBinLogStatement ( const SQLStatement::table_type &tables ) : tables ( tables ) {
}

SQLBinLogStatement::SQLBinLogStatement ( yy::location location, const char *base64, MySQLEventParser *parser ) {
  if(base64 && base64[0]) {
    gsize len;
    guchar *data = g_base64_decode ( base64, &len );
    parser->parse ( location, (char *) data, len, this );
    g_free ( data );
  }
}

SQLBinLogStatement::~SQLBinLogStatement () {

}

std::string SQLBinLogStatement::toString () const {
  return "BINLOG";
}

void SQLBinLogStatement::getTables ( table_type &rt ) const {
  rt = tables;
}

void SQLBinLogStatement::resolve ( SQLParserContext *context ) {

}

void SQLBinLogStatement::walk ( SQLTreeWalker *walker ) {

}

SQLBinLogStatement *SQLBinLogStatement::clone () const {
  return new SQLBinLogStatement ( tables );
}


void SQLBinLogStatement::event ( MySQLBinLogEvent *event, MySQLEventParser *parser ) {
  table_type t = event->getTables ();

  for ( table_type::iterator it = t.begin (); it != t.end (); ++it ) {
    tables[it->first] |= it->second;
  }

  delete event;
}

