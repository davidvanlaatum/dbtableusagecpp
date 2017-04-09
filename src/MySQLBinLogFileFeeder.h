//
// Created by David van Laatum on 9/4/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLBINLOGFILEFEEDER_H
#define DBTABLEUSAGECPP_MYSQLBINLOGFILEFEEDER_H

#include "LogFileFeeder.h"

class MySQLBinLogFileFeeder : public LogFileFeeder {
public:
    MySQLBinLogFileFeeder ( std::ostream *outputLog, std::ostream *errorLog, std::ostream *debugLog, std::ostream *map,
                            boost::program_options::variables_map &variables_map );
protected:
    virtual FILE *fileHandle ();
    virtual std::string fileName ();
    virtual uint64_t fileSize ();
    virtual bool next ();
    virtual void init ( const Host *pHost );
    virtual std::string progressText ();
private:
    FILE *lastHandle;
    int initalOffset;
    int fileNum;
    std::string host;
    std::string user;
    std::string password;
    std::map<std::string, uint64_t> logFiles;
    std::map<std::string, uint64_t>::iterator current;
};


#endif //DBTABLEUSAGECPP_MYSQLBINLOGFILEFEEDER_H
