//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLPARSERCONTEXT_H
#define DBTABLEUSAGECPP_SQLPARSERCONTEXT_H

#include <vector>
#include <list>
#include "location.hh"
#include "SQLParserFailedException.h"
#include "MySQLEventParser.h"
#include "SQLIdentifier.h"

int getNextInput ( char *buf, int max_size );
typedef yy::location location;
namespace SQL {
  class SQLParserCallback;
  class SQLStatement;
#define LINE_BUFFER_LEN 100
#define LINE_BUFFER_COUNT 100
#define MULTILINE_TMPFILE_LIMIT 4096

  class SQLParserContext {
  public:
      SQLParserContext ( SQLParserCallback *callback, std::ostream *output = NULL, std::ostream *error = NULL,
                         std::ostream *debug = NULL );
      virtual ~SQLParserContext ();
      void push ( yy::location &location, SQLStatement *statement );
      std::string &getFileName ();
      void print ();
      MySQLEventParser *getEventParser ();
      void parseComment ( const char *comment );
      void updateTime ( time_t timestamp );
      void setErrorStream ( std::ostream *stream );
      std::ostream &error () const;
      void setOutStream ( std::ostream *ostream );
      void setDebugStream ( std::ostream *debugStream );
      std::ostream &out () const;
      std::ostream &debug () const;
      void error ( location location, std::string msg );
      boost::shared_ptr<SQLIdentifier> getCurrentDatabase ();
      time_t currentTime ();
      void setVerbose ( int verbose );
      int getVerbose () const;
      void setDebug ( int debug );
      int getDebug () const;
      void setExit ();
      uint64_t getLogPos () const;
      void appendMultiLine ( const char *buffer );
      char *getMultiLineBuffer ();
      FILE *getMultiLineBufferFile ();
      bool returnMultiLineBufferAsFile () const;
      void newMultiLineBuffer ();
      void parseFile ( std::string file ) throw ( SQLParserFailedException );
      void parseFileHandle ( FILE *handle, std::string file )
      throw ( SQLParserFailedException );
      void parseString ( std::string buffer ) throw ( SQLParserFailedException );
      void parseStdIn () throw ( SQLParserFailedException );
      void addIgnoreDB ( std::string db );

      inline bool shouldExit () {
        return isShouldExit;
      }

  protected:
      int getNextInput ( char *buf, int max_size );
      friend int::getNextInput ( char *buf, int max_size );

  private:
      std::string fileName;
      MySQLEventParser eventParser;
      uint64_t logPos;
      time_t timestamp;
      SQLParserCallback *callback;
      std::ostream *outStream;
      std::ostream *errorStream;
      std::ostream *debugStream;
      boost::shared_ptr<SQLIdentifier> currentDatabase;
      FILE *multiLineBuffer;
      std::string multiLineBufferString;
      int verbose;
      int debugLevel;
      bool isShouldExit;
      char *lineBuffers[LINE_BUFFER_COUNT];
      size_t lineNumbers[LINE_BUFFER_COUNT];
      size_t lineBufferIndex;
      size_t lastLineOffset;
      size_t lastLineLen;
      size_t lineNum;
      size_t readBytes;
      typedef std::list<std::string> IgnoreDBs;
      IgnoreDBs ignoreDBs;

      void setCurrentDatabase ( boost::shared_ptr<SQLIdentifier> shared_ptr );
      void parse ( std::string file ) throw ( SQLParserFailedException );
      void setupSignalHandler ();
      void clearSignalHandler ();
      void flushLex ();
      void scanString ( const char *str );
      void destroyLex ();
      bool notIgnored ( SQLStatement *pStatement );
  };
}

#endif //DBTABLEUSAGECPP_SQLPARSERCONTEXT_H
