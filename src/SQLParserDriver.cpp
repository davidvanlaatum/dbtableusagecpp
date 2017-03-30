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

SQLParserDriver::SQLParserDriver () {
  errorStream = NULL;
  outStream = NULL;
  debugStream = NULL;
}

SQLParserDriver::SQLParserDriver ( std::ostream *errorStream, std::ostream *outStream, std::ostream *debugStream )
  : errorStream ( errorStream ), outStream ( outStream ), debugStream ( debugStream ) {
}

void SQLParserDriver::parseFile ( std::string file, SQLParserCallback *callback )  throw ( SQLParserFailedException ) {
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
SQLParserDriver::parseString ( std::string buffer, SQLParserCallback *callback ) throw ( SQLParserFailedException ) {
  yy_buffer_state *bufferState = yy_scan_string ( buffer.data () );
  try {
    parse ( "buffer", callback );
  } catch ( ... ) {
    yy_delete_buffer ( bufferState );
    throw;
  }
  yy_delete_buffer ( bufferState );
}

void SQLParserDriver::parseStdIn ( SQLParserCallback *callback )  throw ( SQLParserFailedException ) {
  parse ( "stdin", callback );
}

void SQLParserDriver::parse ( std::string file, SQLParserCallback *callback )  throw ( SQLParserFailedException ) {
  SQLParserContext ctx ( file, callback );
  if ( outStream ) {
    ctx.setOutStream ( outStream );
  }
  if ( errorStream ) {
    ctx.setErrorStream ( errorStream );
  }
  ::yy::SQLParser parser ( ctx );
  if ( debugStream ) {
    parser.set_debug_stream ( *debugStream );
    parser.set_debug_level ( 1 );
  }

  parser.parse ();
}

void SQLParserDriver::setErrorStream ( std::ostream *errorStream ) {
  SQLParserDriver::errorStream = errorStream;
}

void SQLParserDriver::setOutStream ( std::ostream *outStream ) {
  SQLParserDriver::outStream = outStream;
}

void SQLParserDriver::setDebugStream ( std::ostream *debugStream ) {
  SQLParserDriver::debugStream = debugStream;
}
