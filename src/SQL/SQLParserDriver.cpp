//
// Created by David van Laatum on 29/3/17.
//
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "SQLParserDriver.h"
#include "SQLParserContext.h"
#include "SQLObjectList.h"
#include "SQLTable.h"
#include "SQLColumn.h"
#include "SQLComparision.h"
#include "sql-parser.hpp"
extern FILE *yyin;
struct yy_buffer_state;
extern yy_buffer_state *yy_scan_string ( const char *yy_str );
extern "C" void flushLex ();

SQLParserDriver::SQLParserDriver () {
  errorStream = NULL;
  outStream = NULL;
  debugStream = NULL;
}

SQLParserDriver::SQLParserDriver ( std::ostream *errorStream, std::ostream *outStream, std::ostream *debugStream )
  : errorStream ( errorStream ), outStream ( outStream ), debugStream ( debugStream ) {
}

void SQLParserDriver::parseFile ( std::string file, SQLParserCallback *callback )  throw ( SQLParserFailedException ) {
  flushLex ();
  errno = 0;
  if ( ( yyin = fopen ( file.data (), "r" ) ) != NULL ) {
    try {
      parse ( file, callback );
    } catch ( ... ) {
      fclose ( yyin );
      throw;
    }
  } else {
    throw SQLParserFailedException ( "failed to open " + file + ": " + strerror ( errno ) );
  }
  yyin = NULL;
}

void
SQLParserDriver::parseString ( std::string buffer, SQLParserCallback *callback ) throw ( SQLParserFailedException ) {
  flushLex ();
  yy_scan_string ( buffer.data () );
  parse ( "buffer", callback );
}

void SQLParserDriver::parseStdIn ( SQLParserCallback *callback )  throw ( SQLParserFailedException ) {
  flushLex ();
  parse ( "stdin", callback );
}

int yylex_destroy ();

void SQLParserDriver::parse ( std::string file, SQLParserCallback *callback )  throw ( SQLParserFailedException ) {
  if ( callback == NULL ) {
    throw SQLParserFailedException ( "Callback must not be null" );
  }

  SQLParserContext ctx ( file, callback );
  ctx.setVerbose ( verbose );
  ctx.setDebug ( debug );
  if ( outStream ) {
    ctx.setOutStream ( outStream );
  }
  if ( errorStream ) {
    ctx.setErrorStream ( errorStream );
  }
  ::yy::SQLParser parser ( ctx );
  if ( debugStream ) {
    parser.set_debug_stream ( *debugStream );
    if ( debug > 2 ) {
      parser.set_debug_level ( debug - 2 );
    }
  }

  parser.parse ();
  yylex_destroy ();
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

void SQLParserDriver::setVerbose ( int verbose ) {
  this->verbose = verbose;
}

void SQLParserDriver::setDebug ( int debug ) {
  this->debug = debug;
}
