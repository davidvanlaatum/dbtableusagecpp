//
// Created by David van Laatum on 4/4/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLROWWRITEEVENT_H
#define DBTABLEUSAGECPP_MYSQLROWWRITEEVENT_H

#include "MySQLBinLogEvent.h"
#include "MySQLEvents.h"
#include "MySQLEventParser.h"

class MySQLBinLogWriteRowsEvent : public MySQLBinLogEvent {
public:
    MySQLBinLogWriteRowsEvent ( mysql_event *pEvent, MySQLEventParser *pParser );
    virtual ~MySQLBinLogWriteRowsEvent ();
    virtual SQLStatement::table_type getTables () const;

protected:
    SQLStatement::table_type tables;
};


#endif //DBTABLEUSAGECPP_MYSQLROWWRITEEVENT_H
