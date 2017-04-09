//
// Created by David van Laatum on 9/4/17.
//

#ifndef DBTABLEUSAGECPP_CLILOGFILEFEEDER_H
#define DBTABLEUSAGECPP_CLILOGFILEFEEDER_H

#include "LogFileFeeder.h"

class CLILogFileFeeder : public LogFileFeeder {
public:
    CLILogFileFeeder ( std::ostream *outputLog, std::ostream *errorLog, std::ostream *debugLog, std::ostream *progress,
                       const boost::program_options::variables_map &vm );
protected:
    virtual FILE *fileHandle ();
    virtual std::string fileName ();
    virtual uint64_t fileSize ();
    virtual bool next ();
    virtual void init ( const Host *pHost );
private:
    std::vector<std::string> files;
    std::vector<std::string>::iterator current;
    size_t fileNum;
    FILE *lastHandle;
};


#endif //DBTABLEUSAGECPP_CLILOGFILEFEEDER_H
