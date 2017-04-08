//
// Created by David van Laatum on 4/4/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLBINLOGDELETEROWSEVENT_H
#define DBTABLEUSAGECPP_MYSQLBINLOGDELETEROWSEVENT_H

#include "MySQLBinLogEvent.h"
#include "MySQLEvents.h"
#include "MySQLEventParser.h"
namespace SQL {
  class MySQLBinLogDeleteRowsEvent : public MySQLBinLogEvent {

  public:
      MySQLBinLogDeleteRowsEvent ( mysql_event *pEvent, MySQLEventParser *pParser );
      virtual ~MySQLBinLogDeleteRowsEvent ();
      virtual SQLStatement::table_type getTables () const;
  protected:
      SQLStatement::table_type tables;
  };
}


#endif //DBTABLEUSAGECPP_MYSQLBINLOGDELETEROWSEVENT_H
