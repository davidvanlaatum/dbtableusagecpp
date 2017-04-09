//
// Created by David van Laatum on 26/3/17.
//

#include <glib.h>
#include <strings.h>
#include <iostream>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <boost/scoped_ptr.hpp>
#include <iomanip>
#include <sql-parser.hpp>
#include "SQLParserContext.h"
#include "SQLStatement.h"
#include "SQLSetStatement.h"
#include "SQLInteger.h"
#include "SQLUseDatabase.h"
#include "SQLParserCallback.h"
#include "SQLDecimal.h"

extern FILE *yyin;
SQL::SQLParserContext *currentContext;
std::string bytesToString ( uint64_t bytes );

void signalHandler ( int sig ) {
  if ( currentContext ) {
    currentContext->setExit ();
  }
}

bool hasLF ( const char *line ) {
  if ( line == NULL ) {
    return false;
  }
  size_t i = 0;
  while ( line[i] != 0 && line[i] != '\n' ) {
    i++;
  }
  return line[i] == '\n';
}

SQL::SQLParserContext::SQLParserContext ( SQLParserCallback *callback, std::ostream *output, std::ostream *error,
                                     std::ostream *debug ) :
  eventParser ( this ), callback ( callback ), outStream ( output ), errorStream ( error ), debugStream ( debug ) {
  bzero ( lineBuffers, sizeof ( lineBuffers ) );
  bzero ( lineNumbers, sizeof ( lineNumbers ) );
  if ( !errorStream ) {
    errorStream = &std::cerr;
  }
  if ( !outStream ) {
    outStream = &std::cout;
  }
  debugStream = NULL;
  timestamp = 0;
  multiLineBuffer = NULL;
  isShouldExit = false;
  lineNum = 1;
  lineBufferIndex = 0;
  lastLineOffset = 0;
  lastLineLen = 0;
  readBytes = 0;
}

SQL::SQLParserContext::~SQLParserContext () {
  readBytes = 0;
  for ( int i = 0; i < LINE_BUFFER_COUNT; i++ ) {
    if ( lineBuffers[i] ) {
      free ( lineBuffers[i] );
    }
  }
  if ( multiLineBuffer ) {
    fclose ( multiLineBuffer );
  }
}

void SQL::SQLParserContext::push ( yy::location &yylloc, SQLStatement *statement ) {
  boost::scoped_ptr<SQLStatement> autodelete ( statement );
  if ( statement == NULL ) {
    throw SQLParserFailedException ( yylloc, "null statement" );
  }
  statement->resolve ( this );
  if ( SQLUseDatabase *use = dynamic_cast<SQLUseDatabase *>(statement) ) {
    setCurrentDatabase ( use->getName () );
  }

  if ( notIgnored ( statement ) ) {
    if ( verbose && statement->showAtVerboseLevel () <= verbose ) {
      out () << yylloc << " " << *statement << std::endl;
    }

    if ( SQLSetStatement *set = dynamic_cast<SQLSetStatement *>(statement) ) {
      for ( SQLSetStatement::ArgsType::const_iterator it = set->getArgs ().begin (); it != set->getArgs ().end ();
            ++it ) {
        if ( ( *it )->getName () == "TIMESTAMP" ) {
          if ( SQLInteger *t = dynamic_cast<SQLInteger *> (( *it )->getValue ()) ) {
            updateTime ( t->toInt () );
          } else if ( SQLDecimal *d = dynamic_cast<SQLDecimal *>(( *it )->getValue ()) ) {
            updateTime ( d->getWhole () );
          } else {
            std::stringstream buf;
            buf << "invalid value for timestamp " << ( *it )->getValue ();
            error ( yylloc, buf.str () );
          }
        }
      }
    }

    callback->statement ( yylloc, statement, this );
  }
}

std::string &SQL::SQLParserContext::getFileName () {
  return fileName;
}

void SQL::SQLParserContext::print () {
  eventParser.dump ();
}

SQL::MySQLEventParser *SQL::SQLParserContext::getEventParser () {
  return &eventParser;
}

void SQL::SQLParserContext::parseComment ( const char *comment ) {
  if ( strncasecmp ( comment, "# at ", 5 ) == 0 ) {
    logPos = strtoull ( comment + 5, NULL, 10 );
  }
}

void SQL::SQLParserContext::updateTime ( time_t timestamp ) {
  this->timestamp = timestamp;
}

void SQL::SQLParserContext::setErrorStream ( std::ostream *stream ) {
  errorStream = stream;
}

std::ostream &SQL::SQLParserContext::error () const {
  return *errorStream;
}

void SQL::SQLParserContext::setOutStream ( std::ostream *ostream ) {
  outStream = ostream;
}

void SQL::SQLParserContext::setDebugStream ( std::ostream *debugStream ) {
  SQLParserContext::debugStream = debugStream;
}

std::ostream &SQL::SQLParserContext::out () const {
  return *outStream;
}

void SQL::SQLParserContext::error ( location location, std::string msg ) {
  std::stringstream error;
  bool lineContinue = false;
  error << location << ": " << msg << std::endl;
  int linesOutput = 0;
  std::stringstream s;
  s << location.end.line << ": ";
  int lineNumberLen = (int) s.str ().size ();
  size_t lineLen = 0;
  size_t startLine = location.begin.line;
  if ( startLine > 1 && location.begin.column <= 1 ) {
    startLine--;
  }
  for ( size_t i = 0; i < LINE_BUFFER_COUNT; i++ ) {
    size_t x = ( lineBufferIndex + i + 1 ) % LINE_BUFFER_COUNT;
    if ( startLine <= lineNumbers[x] && location.end.line >= lineNumbers[x] ) {
      if ( !lineContinue ) {
        linesOutput++;
        error << std::setw ( lineNumberLen - 2 ) << lineNumbers[x] << ": ";
      }
      error << lineBuffers[x];
      lineContinue = !hasLF ( lineBuffers[x] );
      lineLen += strlen ( lineBuffers[x] );
      if ( !lineContinue ) {
        std::stringstream indicator;
        if ( lineNumbers[x] == location.begin.line && lineNumbers[x] == location.end.line ) {
          indicator << std::setw ( location.begin.column + lineNumberLen ) << "^";
          if ( location.begin.column + 1 < location.end.column ) {
            int n = location.end.column - location.begin.column - 1;
            if ( n > lineLen - location.begin.column ) {
              n = int ( lineLen - location.begin.column );
            }
            indicator << std::setfill ( '-' ) << std::setw ( n ) << "^";
          }
          indicator << std::endl;
        } else if ( lineNumbers[x] == location.begin.line ) {
          indicator << std::setw ( location.begin.column + lineNumberLen ) << "^" << std::setfill ( '-' )
                    << std::setw ( int ( lineLen - location.begin.column ) ) << ">" << std::endl;
        } else if ( lineNumbers[x] == location.end.line ) {
          indicator << std::setfill ( '-' ) << std::setw ( location.end.column + lineNumberLen ) << "^" << std::endl;
        }
        error << indicator.str ();
        lineLen = 0;
      }
    }
  }
//  if ( linesOutput == 0 ) {
//    error << "Failed to find any lines to output lines we have are: ";
//    for ( size_t i = 0; i < LINE_BUFFER_COUNT; i++ ) {
//      size_t x = ( lineBufferIndex + i + 1 ) % LINE_BUFFER_COUNT;
//      error << x << "=" << lineNumbers[x] << ",";
//    }
//    error << std::endl;
//  }
  *errorStream << error.str ();
}

void SQL::SQLParserContext::parseFile ( std::string file )  throw ( SQLParserFailedException ) {
  FILE *in = NULL;
  if ( ( in = fopen ( file.data (), "r" ) ) != NULL ) {
    try {
      parseFileHandle ( in, file );
      fclose ( in );
    } catch ( ... ) {
      fclose ( in );
      throw;
    }
  } else {
    throw SQLParserFailedException ( "failed to open " + file + ": " + strerror ( errno ) );
  }
}

void SQL::SQLParserContext::parseFileHandle ( FILE *handle, std::string file ) throw ( SQLParserFailedException ) {
  flushLex ();
  errno = 0;
  yyin = handle;
  parse ( file );
}

void
SQL::SQLParserContext::parseString ( std::string buffer ) throw ( SQLParserFailedException ) {
  flushLex ();
  scanString ( buffer.data () );
  parse ( "buffer" );
}

void SQL::SQLParserContext::parseStdIn ()  throw ( SQLParserFailedException ) {
  flushLex ();
  parse ( "stdin" );
}

void SQL::SQLParserContext::setupSignalHandler () {
  struct sigaction s;
  bzero ( &s, sizeof ( s ) );
  s.sa_handler = signalHandler;
  s.sa_flags = SA_RESETHAND | SA_RESTART;
  sigaction ( SIGTERM, &s, NULL );
  sigaction ( SIGINT, &s, NULL );
  sigaction ( SIGHUP, &s, NULL );
}

void SQL::SQLParserContext::clearSignalHandler () {

}

void SQL::SQLParserContext::parse ( std::string file )  throw ( SQLParserFailedException ) {
  if ( callback == NULL ) {
    throw SQLParserFailedException ( "Callback must not be null" );
  }
  fileName = file;
  ::yy::SQLParser parser ( *this );
  if ( debugStream ) {
    parser.set_debug_stream ( *debugStream );
    if ( debugLevel > 2 ) {
      parser.set_debug_level ( debugLevel - 2 );
    }
  }
  try {
    currentContext = this;
    setupSignalHandler ();
    parser.parse ();
    clearSignalHandler ();
    currentContext = NULL;
    destroyLex ();
  } catch ( ... ) {
    clearSignalHandler ();
    currentContext = NULL;
    destroyLex ();
    throw;
  }
}

boost::shared_ptr<SQL::SQLIdentifier> SQL::SQLParserContext::getCurrentDatabase () {
  return currentDatabase;
}

void SQL::SQLParserContext::setCurrentDatabase ( boost::shared_ptr<SQLIdentifier> name ) {
  currentDatabase = name;
}

time_t SQL::SQLParserContext::currentTime () {
  return timestamp;
}

void SQL::SQLParserContext::setVerbose ( int verbose ) {
  this->verbose = verbose;
}

int SQL::SQLParserContext::getVerbose () const {
  return verbose;
}

void SQL::SQLParserContext::setDebug ( int debug ) {
  this->debugLevel = debug;
}

int SQL::SQLParserContext::getDebug () const {
  return debugLevel;
}

uint64_t SQL::SQLParserContext::getLogPos () const {
  return logPos;
}

void SQL::SQLParserContext::newMultiLineBuffer () {
  if ( multiLineBuffer ) {
    fclose ( multiLineBuffer );
  }
  multiLineBuffer = NULL;
  multiLineBufferString.clear ();
}

void SQL::SQLParserContext::appendMultiLine ( const char *buffer ) {
  size_t len = strlen ( buffer );
  if ( multiLineBuffer ) {
    guchar *data = g_base64_decode ( buffer, &len );
    fwrite ( data, len, 1, multiLineBuffer );
    g_free ( data );
  } else if ( multiLineBufferString.size () + len > MULTILINE_TMPFILE_LIMIT ) {
    errno = 0;
    multiLineBuffer = tmpfile ();
    if ( !multiLineBuffer ) {
      throw SQLParserFailedException ( std::string ( "Failed to create temporary file for multi-line buffer: " ) +
                                       strerror ( errno ) );
    }
    if ( !multiLineBufferString.empty () ) {
      appendMultiLine ( multiLineBufferString.c_str () );
      multiLineBufferString.clear ();
    }
    appendMultiLine ( buffer );
  } else {
    multiLineBufferString.append ( buffer );
  }
}

char *SQL::SQLParserContext::getMultiLineBuffer () {
  char *rt = strdup ( multiLineBufferString.c_str () );
  multiLineBufferString.clear ();
  return rt;
}

FILE *SQL::SQLParserContext::getMultiLineBufferFile () {
  FILE *tmp = multiLineBuffer;
  multiLineBuffer = NULL;
  return tmp;
}

bool SQL::SQLParserContext::returnMultiLineBufferAsFile () const {
  return multiLineBuffer != NULL;
}


void SQL::SQLParserContext::setExit () {
  isShouldExit = true;
}

int SQL::SQLParserContext::getNextInput ( char *buf, int max_size ) {
  int rt = 0;
  if ( !feof ( yyin ) ) {
    if ( lastLineOffset >= lastLineLen ) {
      if ( hasLF ( lineBuffers[lineBufferIndex] ) ) { // if the last line buffer ends in \n we are now on a new line
        lineNum++;
      }
      lineBufferIndex++;
      if ( lineBufferIndex >= LINE_BUFFER_COUNT ) {
        lineBufferIndex = 0;
      }
      if ( !lineBuffers[lineBufferIndex] ) {
        lineBuffers[lineBufferIndex] = (char *) malloc ( LINE_BUFFER_LEN );
      }
      if ( !fgets ( lineBuffers[lineBufferIndex], LINE_BUFFER_LEN, yyin ) ) {
        lineBuffers[lineBufferIndex][0] = 0;
      } else if ( currentContext->getDebug () ) {
        currentContext->debug () << "Read '" << lineBuffers[lineBufferIndex] << "'" << std::endl;
      }
      lastLineLen = strlen ( lineBuffers[lineBufferIndex] );
      readBytes += lastLineLen;
      lastLineOffset = 0;
      lineNumbers[lineBufferIndex] = lineNum;
    }
    if ( lastLineOffset < lastLineLen ) {
      buf[0] = lineBuffers[lineBufferIndex][lastLineOffset++];
      return 1;
    }
  }
  return rt;
}

std::ostream &SQL::SQLParserContext::debug () const {
  return *debugStream;
}

void SQL::SQLParserContext::addIgnoreDB ( std::string db ) {
  ignoreDBs.push_back ( db );
}

bool SQL::SQLParserContext::notIgnored ( SQLStatement *pStatement ) {
  bool rt = true;

  SQLStatement::table_type tables;
  pStatement->getTables ( tables );
  size_t ignored = 0;
  for ( SQLStatement::table_type::iterator it = tables.begin (); it != tables.end (); ++it ) {
    for ( IgnoreDBs::iterator it2 = ignoreDBs.begin (); it2 != ignoreDBs.end (); ++it2 ) {
      if ( it->first->getSchema ()->getId () == *it2 ) {
        ignored++;
        break;
      }
    }
  }
  if ( ignored == tables.size () && !tables.empty () ) {
    rt = false;
  }

  return rt;
}

void yyerror ( location *yylloc, SQL::SQLParserContext &ctx, const char *s, ... ) {
  va_list ap;
  va_start( ap, s );
  char *msg = NULL;
  vasprintf ( &msg, s, ap );
  ctx.error ( *yylloc, msg );
  free ( msg );
}

void adjustLines ( location *location, char *text ) {
  char *pos = NULL;
  int lines = 0;
  while ( ( pos = index ( text, '\n' ) ) != NULL ) {
    lines++;
    text = pos + 1;
  }
  if ( lines ) {
    location->lines ( lines );
    location->columns ( (int) strlen ( text ) );
  }
}

int getNextInput ( char *buf, int max_size ) {
  return currentContext->getNextInput ( buf, max_size );
}
