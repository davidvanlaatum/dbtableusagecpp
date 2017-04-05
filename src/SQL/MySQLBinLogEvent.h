//
// Created by David van Laatum on 4/4/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLBINLOGEVENT_H
#define DBTABLEUSAGECPP_MYSQLBINLOGEVENT_H

#include "SQLStatement.h"

class MySQLBinLogEvent {
public:
    virtual SQLStatement::table_type getTables () const = 0;
    virtual ~MySQLBinLogEvent ();
};


#endif //DBTABLEUSAGECPP_MYSQLBINLOGEVENT_H
