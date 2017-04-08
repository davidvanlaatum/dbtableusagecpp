//
// Created by David van Laatum on 26/3/17.
//

#include <glib.h>
#include <iostream>
#include <sys/mman.h>
#include <sstream>
#include "SQLBinLogStatement.h"
#include "MySQLBinLogEvent.h"

SQL::SQLBinLogStatement::SQLBinLogStatement ( const SQLStatement::table_type &tables ) : tables ( tables ) {
}

SQL::SQLBinLogStatement::SQLBinLogStatement ( yy::location location, const char *base64, MySQLEventParser *parser ) {
  if ( base64 && base64[0] ) {
    gsize len;
    guchar *data = g_base64_decode ( base64, &len );
    parser->parse ( location, (char *) data, len, this );
    g_free ( data );
  }
}

SQL::SQLBinLogStatement::SQLBinLogStatement ( yy::location location, FILE *file, MySQLEventParser *parser ) {
  int fd = fileno ( file );
  long len = ftell ( file );
  char *buffer = (char *) mmap ( NULL, (size_t) len, PROT_READ, MAP_SHARED, fd, 0 );
  fclose ( file );
  parser->parse ( location, buffer, (size_t) len, this );
  munmap ( buffer, (size_t) len );
}

SQL::SQLBinLogStatement::~SQLBinLogStatement () {

}

std::string SQL::SQLBinLogStatement::toString () const {
  std::stringstream s;
  s << "BINLOG";
  if ( !tables.empty () ) {
    s << "(";
    for ( table_type::const_iterator it = tables.begin (); it != tables.end ();) {
      s << it->first->getName ()->getId () << "="
        << (it->second & INSERT ? "I" : "-")
        << (it->second & UPDATE ? "U" : "-")
        << (it->second & DELETE ? "D" : "-")
        << (++it != tables.end () ? "," : "" );
    }
    s << ")";
  }
  return s.str ();
}

void SQL::SQLBinLogStatement::getTables ( table_type &rt ) const {
  rt = tables;
}

void SQL::SQLBinLogStatement::resolve ( SQLParserContext *context ) {

}

void SQL::SQLBinLogStatement::walk ( SQLTreeWalker *walker ) {

}


SQL::SQLBinLogStatement *SQL::SQLBinLogStatement::clone () const {
  return new SQLBinLogStatement ( tables );
}

void SQL::SQLBinLogStatement::event ( MySQLBinLogEvent *event, MySQLEventParser *parser ) {
  table_type t = event->getTables ();

  for ( table_type::iterator it = t.begin (); it != t.end (); ++it ) {
    tables[it->first] |= it->second;
  }

  delete event;
}

size_t SQL::SQLBinLogStatement::showAtVerboseLevel () const {
  return 1;
}

