//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_LOGFILEFEATCHER_H
#define DBTABLEUSAGECPP_LOGFILEFEATCHER_H

#include <string>
#include <list>
#include "soci.h"
#include "Host.h"

using namespace soci;

class LogFileFetcher {
public:
    LogFileFetcher ();
    void setConnection ( std::string host, std::string user, std::string password );
    bool fetchLogs ( const Host *host );
    std::string currentLogFile ();
    bool hasMoreLogs ();
    FILE *fileHandle ();
    void next ();
    uint64_t currentLogFileSize ();
private:
    int initalOffset;
    std::string host;
    std::string user;
    std::string password;
    session sql;
    std::map<std::string, uint64_t> logFiles;
    std::map<std::string, uint64_t>::iterator current;
};


#endif //DBTABLEUSAGECPP_LOGFILEFEATCHER_H
