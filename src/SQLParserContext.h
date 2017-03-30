//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLPARSERCONTEXT_H
#define DBTABLEUSAGECPP_SQLPARSERCONTEXT_H

#include <vector>
#include "SQLBinLogStatement.h"
#include "SQLObjectList.h"
#include "SetStatement.h"
#include "SQLDeleteStatement.h"
#include "SQLString.h"
#include "SQLDefault.h"
#include "SQLInteger.h"
#include "SQLParserCallback.h"

class SQLParserContext {
public:
    SQLParserContext ( std::string fileName, SQLParserCallback *callback );
    void push ( yy::location yylloc, SQLStatement *statement );
    const std::string &getFileName () const;
    void print ();
    MySQLEventParser *getEventParser ();
    void parseComment ( const char *comment );
    void updateDB ( std::string db );
    void updateTime ( time_t timestamp );
    void setErrorStream ( std::ostream *stream );
    std::ostream &error () const;
    void setOutStream ( std::ostream *ostream );
    std::ostream &out () const;
private:
    std::string fileName;
    MySQLEventParser eventParser;
    uint64_t logPos;
    time_t timestamp;
    SQLParserCallback *callback;
    std::ostream *errorStream;
    std::ostream *outStream;
};


#endif //DBTABLEUSAGECPP_SQLPARSERCONTEXT_H
