//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLPARSERCONTEXT_H
#define DBTABLEUSAGECPP_SQLPARSERCONTEXT_H

#include <vector>
#include "SQLParserCallback.h"
#include "MySQLEventParser.h"
#include "SQLIdentifier.h"

class SQLParserCallback;

class SQLParserContext {
public:
    SQLParserContext ( std::string fileName, SQLParserCallback *callback );
    virtual ~SQLParserContext ();
    void push ( yy::location &yylloc, SQLStatement *statement );
    std::string &getFileName ();
    void print ();
    MySQLEventParser *getEventParser ();
    void parseComment ( const char *comment );
    void updateTime ( time_t timestamp );
    void setErrorStream ( std::ostream *stream );
    std::ostream &error () const;
    void setOutStream ( std::ostream *ostream );
    std::ostream &out () const;
    void error ( location location, std::string msg );
    boost::shared_ptr<SQLIdentifier> getCurrentDatabase ();
    time_t currentTime ();
    void setVerbose ( int verbose );
    int getVerbose () const;
    void setDebug ( int debug );
    int getDebug () const;
    uint64_t getLogPos () const;
    void appendMultiLine(const char *buffer);
    char *getMultiLineBuffer();
    FILE *getMultiLineBufferFile();
private:
    std::string fileName;
    MySQLEventParser eventParser;
    uint64_t logPos;
    time_t timestamp;
    SQLParserCallback *callback;
    std::ostream *errorStream;
    std::ostream *outStream;
    boost::shared_ptr<SQLIdentifier> currentDatabase;
    FILE *multiLineBuffer;

    void setCurrentDatabase ( boost::shared_ptr<SQLIdentifier> shared_ptr );
    int verbose;
    int debug;
    void initBuffers () const;
};


#endif //DBTABLEUSAGECPP_SQLPARSERCONTEXT_H
