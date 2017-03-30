//
// Created by David van Laatum on 29/3/17.
//
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "SQLParserDriver.h"
#include "SQLParserContext.h"
#include "sql-parser.hpp"
extern FILE *yyin;
struct yy_buffer_state;
extern yy_buffer_state *yy_scan_string ( const char *yy_str );
extern void yy_delete_buffer ( yy_buffer_state *b );


void SQLParserDriver::parseFile ( std::string file, SQLParserCallback *callback )  throw ( std::runtime_error ) {
  errno = 0;
  if ( ( yyin = fopen ( file.data (), "r" ) ) != NULL ) {
    try {
      parse ( file, callback );
    } catch ( ... ) {
      fclose ( yyin );
      throw;
    }
    fclose ( yyin );
  } else {
    throw SQLParserFailedException ( "failed to open " + file + ": " + strerror ( errno ) );
  }
  yyin = NULL;
}

void
SQLParserDriver::parseString ( std::string buffer, SQLParserCallback *callback ) throw ( std::runtime_error ) {
  yy_buffer_state *bufferState = yy_scan_string ( buffer.data () );
  try {
    parse ( "buffer", callback );
  } catch ( ... ) {
    yy_delete_buffer ( bufferState );
    throw;
  }
  yy_delete_buffer ( bufferState );
}

void SQLParserDriver::parseStdIn ( SQLParserCallback *callback )  throw ( std::runtime_error ) {
  parse ( "stdin", callback );
}

void SQLParserDriver::parse ( std::string file, SQLParserCallback *callback )  throw ( std::runtime_error ) {
  struct timeval start, end, diff;

  gettimeofday ( &start, NULL );
  SQLParserContext ctx ( file, callback );
  ::yy::SQLParser parser ( ctx );
//  parser.set_debug_level ( 1 );

  parser.parse ();

  gettimeofday ( &end, NULL );
  timersub( &end, &start, &diff );

  ctx.out () << "Runtime " << diff.tv_sec << "." << diff.tv_usec << std::endl;
}
