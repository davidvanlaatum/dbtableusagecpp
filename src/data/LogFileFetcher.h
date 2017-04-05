//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_LOGFILEFEATCHER_H
#define DBTABLEUSAGECPP_LOGFILEFEATCHER_H

#include <string>
#include <list>
#include "soci.h"

using namespace soci;

class LogFileFetcher {
public:
    void setConnection ( std::string host, std::string user, std::string password );
    bool fetchLogs ();
    std::string currentLogFile ();
    bool hasMoreLogs ();
    FILE *fileHandle ();
    void next();
private:
    std::string host;
    std::string user;
    std::string password;
    session sql;
    std::list<std::string> logFiles;
    std::list<std::string>::iterator current;
};


#endif //DBTABLEUSAGECPP_LOGFILEFEATCHER_H
