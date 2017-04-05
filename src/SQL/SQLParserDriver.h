//
// Created by David van Laatum on 29/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLPARSER_H
#define DBTABLEUSAGECPP_SQLPARSER_H
#include <string>
#include "SQLParserCallback.h"
#include "SQLParserFailedException.h"

class SQLParserDriver {
public:
    SQLParserDriver ();
    SQLParserDriver ( std::ostream *errorStream, std::ostream *outStream, std::ostream *debugStream );
    void parseFile ( std::string file, SQLParserCallback *callback ) throw ( SQLParserFailedException );
    void parseFileHandle ( FILE *handle, std::string file, SQLParserCallback *callback ) throw ( SQLParserFailedException );
    void parseString ( std::string buffer, SQLParserCallback *callback ) throw ( SQLParserFailedException );
    void parseStdIn ( SQLParserCallback *callback ) throw ( SQLParserFailedException );
    void setErrorStream ( std::ostream *errorStream );
    void setOutStream ( std::ostream *outStream );
    void setDebugStream ( std::ostream *debugStream );
    void setVerbose ( int verbose );
    void setDebug ( int debug );
protected:
    void parse ( std::string file, SQLParserCallback *callback ) throw ( SQLParserFailedException );
    std::ostream *errorStream;
    std::ostream *outStream;
    std::ostream *debugStream;
    int verbose;
    int debug;
};

#endif //DBTABLEUSAGECPP_SQLPARSER_H
