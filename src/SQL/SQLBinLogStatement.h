//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_BINLOGSTATEMENT_H
#define DBTABLEUSAGECPP_BINLOGSTATEMENT_H

#include "SQLStatement.h"
#include "MySQLEventParser.h"
#include "location.hh"

class SQLBinLogStatement : public SQLStatement, public MySQLEventParserCallback {
public:
    SQLBinLogStatement ( yy::location yylloc, const char *data, MySQLEventParser *parser );
    SQLBinLogStatement ( const table_type &tables );
    virtual ~SQLBinLogStatement ();
    virtual std::string toString () const;
    virtual void getTables ( table_type &rt ) const;
    virtual void resolve ( SQLParserContext *context );
    virtual void walk ( SQLTreeWalker *walker );
    virtual SQLBinLogStatement *clone () const;
    virtual void event ( MySQLBinLogEvent *event, MySQLEventParser *parser );
private:
    table_type tables;
};


#endif //DBTABLEUSAGECPP_BINLOGSTATEMENT_H
