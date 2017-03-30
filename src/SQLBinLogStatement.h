//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_BINLOGSTATEMENT_H
#define DBTABLEUSAGECPP_BINLOGSTATEMENT_H

#include "SQLStatement.h"
#include "mysqlevents/MySQLEventParser.h"
#include "location.hh"

class SQLBinLogStatement : public SQLStatement {
public:
    SQLBinLogStatement ( yy::location yylloc, const char *data, MySQLEventParser *parser );
    virtual ~SQLBinLogStatement ();
    virtual std::string toString () const;
};


#endif //DBTABLEUSAGECPP_BINLOGSTATEMENT_H
