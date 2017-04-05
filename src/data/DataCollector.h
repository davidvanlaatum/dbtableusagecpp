//
// Created by David van Laatum on 1/4/17.
//

#ifndef DBTABLEUSAGECPP_DATACOLLECTOR_H
#define DBTABLEUSAGECPP_DATACOLLECTOR_H

#include <map>
#include "boost/scoped_ptr.hpp"
#include "SQLParserCallback.h"
#include "SQLObject.h"
#include "Host.h"

class DataCollector : public SQLParserCallback {
public:
    DataCollector ();
    virtual void statement ( location &location, SQLStatement *statement, SQLParserContext *context );
    void dump ();

private:
    typedef std::map<std::string, boost::shared_ptr<SQLObject> > variables_type;
    variables_type variables;
    boost::shared_ptr<Host> host;
    int statements;
    timeval lastUpdate;
    timeval start;
    time_t lastTime;
    int lastStatements;
    time_t firstStatement;

    class Walker : public SQLTreeWalker {
    public:
        Walker ( boost::shared_ptr<Host> &host, SQLParserContext *context );
        virtual void walk ( SQLObject *object );
    private:
        boost::shared_ptr<Host> host;
        SQLParserContext *ctx;
    };
};


#endif //DBTABLEUSAGECPP_DATACOLLECTOR_H
