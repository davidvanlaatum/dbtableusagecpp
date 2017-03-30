//
// Created by David van Laatum on 26/3/17.
//

#include <glib.h>
#include <iostream>
#include "SQLBinLogStatement.h"

SQLBinLogStatement::SQLBinLogStatement ( yy::location location, const char *base64, MySQLEventParser *parser ) {
  gsize len;
  guchar *data = g_base64_decode ( base64, &len );
  parser->parse ( location, (char *) data, len );
  g_free ( data );
}

SQLBinLogStatement::~SQLBinLogStatement () {

}

std::string SQLBinLogStatement::toString () const {
  return "BINLOG";
}

