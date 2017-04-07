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
#include "SQLParserContext.h"
#include "SQLParserFailedException.h"
#include "SQLStatement.h"
#include "SQLSetStatement.h"
#include "SQLInteger.h"
#include "SQLUseDatabase.h"

extern FILE *yyin;
#define LINE_BUFFER_LEN 100
#define LINE_BUFFER_COUNT 100
char *lineBuffers[LINE_BUFFER_COUNT] = { 0 };
size_t lineNumbers[LINE_BUFFER_COUNT] = { 0 };
size_t lineBufferIndex = 0;
size_t lastLineOffset = 0;
size_t lastLineLen = 0;
size_t lineNum = 0;
size_t readBytes = 0;

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

SQLParserContext::SQLParserContext ( std::string fileName, SQLParserCallback *callback ) : fileName ( fileName ),
                                                                                           eventParser ( this ),
                                                                                           callback ( callback ) {
  errorStream = &std::cerr;
  outStream = &std::cout;
  timestamp = 0;
  initBuffers ();
  multiLineBuffer = NULL;
  isShouldExit = false;
}

SQLParserContext::~SQLParserContext () {
  initBuffers ();
  if ( multiLineBuffer ) {
    fclose ( multiLineBuffer );
  }
}

void SQLParserContext::initBuffers () const {
  readBytes = 0;
  for ( int i = 0; i < LINE_BUFFER_COUNT; i++ ) {
    if ( lineBuffers[i] ) {
      free ( lineBuffers[i] );
    }
  }
  bzero ( lineNumbers, sizeof ( lineNumbers ) );
  bzero ( lineBuffers, sizeof ( lineBuffers ) );
  lineNum = 1;
}

void SQLParserContext::push ( yy::location &yylloc, SQLStatement *statement ) {
  boost::scoped_ptr<SQLStatement> autodelete ( statement );
  if ( statement == NULL ) {
    throw SQLParserFailedException ( yylloc, "null statement" );
  }
  statement->resolve ( this );
  if ( verbose ) {
    out () << yylloc << " " << *statement << std::endl;
  }

  if ( SQLSetStatement *set = dynamic_cast<SQLSetStatement *>(statement) ) {
    for ( SQLSetStatement::ArgsType::const_iterator it = set->getArgs ().begin (); it != set->getArgs ().end ();
          ++it ) {
      if ( ( *it )->getName () == "TIMESTAMP" ) {
        if ( SQLInteger *t = dynamic_cast<SQLInteger *> (( *it )->getValue ()) ) {
          updateTime ( t->toInt () );
        } else {
          error () << yylloc << " invalid value for timestamp " << ( *it )->getValue () << std::endl;
        }
      }
    }
  }

  if ( SQLUseDatabase *use = dynamic_cast<SQLUseDatabase *>(statement) ) {
    setCurrentDatabase ( use->getName () );
  }

  callback->statement ( yylloc, statement, this );
}

std::string &SQLParserContext::getFileName () {
  return fileName;
}

void SQLParserContext::print () {
  eventParser.dump ();
}

MySQLEventParser *SQLParserContext::getEventParser () {
  return &eventParser;
}

void SQLParserContext::parseComment ( const char *comment ) {
  if ( strncasecmp ( comment, "# at ", 5 ) == 0 ) {
    logPos = strtoull ( comment + 5, NULL, 10 );
  }
}

void SQLParserContext::updateTime ( time_t timestamp ) {
  this->timestamp = timestamp;
}

void SQLParserContext::setErrorStream ( std::ostream *stream ) {
  errorStream = stream;
}

std::ostream &SQLParserContext::error () const {
  return *errorStream;
}

void SQLParserContext::setOutStream ( std::ostream *ostream ) {
  outStream = ostream;
}

std::ostream &SQLParserContext::out () const {
  return *outStream;
}

void SQLParserContext::error ( location location, std::string msg ) {
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

boost::shared_ptr<SQLIdentifier> SQLParserContext::getCurrentDatabase () {
  return currentDatabase;
}

void SQLParserContext::setCurrentDatabase ( boost::shared_ptr<SQLIdentifier> name ) {
  currentDatabase = name;
}

time_t SQLParserContext::currentTime () {
  return timestamp;
}

void SQLParserContext::setVerbose ( int verbose ) {
  this->verbose = verbose;
}

int SQLParserContext::getVerbose () const {
  return verbose;
}

void SQLParserContext::setDebug ( int debug ) {
  this->debug = debug;
}

int SQLParserContext::getDebug () const {
  return debug;
}

uint64_t SQLParserContext::getLogPos () const {
  return logPos;
}

void SQLParserContext::appendMultiLine ( const char *buffer ) {
  if ( !multiLineBuffer ) {
    multiLineBuffer = tmpfile ();
  }
  size_t len = strlen ( buffer );
  guchar *data = g_base64_decode ( buffer, &len );
  fwrite ( data, len, 1, multiLineBuffer );
  g_free ( data );
}

char *SQLParserContext::getMultiLineBuffer () {
  char *rt = NULL;
  if ( multiLineBuffer ) {
    errno = 0;
    size_t len = (size_t) ftell ( multiLineBuffer );
    if ( errno != 0 ) {
      throw std::runtime_error ( strerror ( errno ) );
    }
    if ( len > 1024 * 1024 ) {
      *errorStream << "Truncating buffer of length " << len << std::endl;
      len = 4096;
    }
    rt = (char *) malloc ( len + 1 );
    rt[len] = 0;
    rewind ( multiLineBuffer );
    fread ( rt, 1, len, multiLineBuffer );
    fclose ( multiLineBuffer );
    multiLineBuffer = NULL;
  }
  return rt;
}

FILE *SQLParserContext::getMultiLineBufferFile () {
  FILE *tmp = multiLineBuffer;
  multiLineBuffer = NULL;
  return tmp;
}

void SQLParserContext::setExit () {
  isShouldExit = true;
}

void yyerror ( location *yylloc, SQLParserContext &ctx, const char *s, ... ) {
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

std::string bytesToString ( uint64_t bytes );

int getNextInput ( char *buf, int max_size ) {
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
