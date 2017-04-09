//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_DATACOLLECTOR_H
#define DBTABLEUSAGECPP_DATACOLLECTOR_H

#include <map>
#include <stdint.h>
#include <location.hh>
#include "boost/scoped_ptr.hpp"
#include "SQLParserCallback.h"
#include "SQLObject.h"
#include "Host.h"
#include "DataStore.h"

class DataCollector : public SQL::SQLParserCallback {
public:
    DataCollector ();
    virtual void statement ( yy::location &location, SQL::SQLStatement *statement, SQL::SQLParserContext *context );
    void dump ();
    void setCurrentFileSize ( uint64_t currentFileSize );
    void setDataStore ( DataStore *pStore );
    void setMonitoredHost ( const std::string &host );
    Host *getHost () const;
    void setCommitInterval ( size_t interval );
    void setProgressStream ( std::ostream *progress );
    void setOutputStream ( std::ostream *output );
    void startNewFile();
private:
    typedef std::map<std::string, boost::shared_ptr<SQL::SQLObject> > variables_type;
    variables_type variables;
    boost::shared_ptr<Host> host;
    struct {
        time_t time;
        size_t statements;
        size_t transactions;
        uint64_t logPos;
    } now, last;
    struct {
        timeval time;
        time_t statement;
    } start;
    timeval lastUpdate;
    uint64_t currentFileSize;
    size_t commitInterval;
    bool inTransaction;
    DataStore *pStore;
    std::ostream *progress;
    std::ostream *output;

    class Walker : public SQL::SQLTreeWalker {
    public:
        Walker ( boost::shared_ptr<Host> &host, SQL::SQLParserContext *context );
        virtual void walk ( SQL::SQLObject *object );
    private:
        boost::shared_ptr<Host> host;
        SQL::SQLParserContext *ctx;
    };
};


#endif //DBTABLEUSAGECPP_DATACOLLECTOR_H
