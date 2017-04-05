//
// Created by David van Laatum on 4/4/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLBINLOGUPDATEROWSEVENT_H
#define DBTABLEUSAGECPP_MYSQLBINLOGUPDATEROWSEVENT_H

#include "MySQLBinLogEvent.h"
#include "MySQLEvents.h"
#include "MySQLEventParser.h"

class MySQLBinLogUpdateRowsEvent : public MySQLBinLogEvent {

public:
    MySQLBinLogUpdateRowsEvent ( mysql_event *pEvent, MySQLEventParser *pParser );
    virtual ~MySQLBinLogUpdateRowsEvent ();
    virtual SQLStatement::table_type getTables () const;

protected:
    SQLStatement::table_type tables;
};


#endif //DBTABLEUSAGECPP_MYSQLBINLOGUPDATEROWSEVENT_H
