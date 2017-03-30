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
    void parseFile ( std::string file, SQLParserCallback *callback ) throw ( std::runtime_error );
    void parseString ( std::string buffer, SQLParserCallback *callback ) throw ( std::runtime_error );
    void parseStdIn ( SQLParserCallback *callback ) throw ( std::runtime_error );
protected:
    void parse ( std::string file, SQLParserCallback *callback ) throw ( std::runtime_error );
};


#endif //DBTABLEUSAGECPP_SQLPARSER_H
