//
// Created by David van Laatum on 9/4/17.
//

#ifndef DBTABLEUSAGECPP_LOGFILEFEEDER_H
#define DBTABLEUSAGECPP_LOGFILEFEEDER_H

#include <cstdio>
#include <string>
#include <ostream>
#include <boost/program_options/variables_map.hpp>
#include <Host.h>
#include <SQLParserContext.h>
class DataCollector;

/*abstract*/ class LogFileFeeder {
public:
    LogFileFeeder ( std::ostream *outputLog, std::ostream *errorLog, std::ostream *debugLog, std::ostream *progress,
                    const boost::program_options::variables_map &vm );
    virtual int feed ( DataCollector *collector );
protected:
    const boost::program_options::variables_map &vm;
    std::ostream *outputLog;
    std::ostream *errorLog;
    std::ostream *debugLog;
    std::ostream *progress;

    virtual FILE *fileHandle () = 0;
    virtual std::string fileName () = 0;
    virtual uint64_t fileSize() = 0;
    virtual bool next () = 0;
    virtual void init ( const Host *pHost ) = 0;
    virtual void setupContext ( SQL::SQLParserContext &context );
    virtual std::string progressText ();
};


#endif //DBTABLEUSAGECPP_LOGFILEFEEDER_H
