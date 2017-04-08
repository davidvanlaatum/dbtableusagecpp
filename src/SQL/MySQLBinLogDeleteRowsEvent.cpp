//
// Created by David van Laatum on 4/4/17.
//

#include "MySQLBinLogDeleteRowsEvent.h"

SQL::MySQLBinLogDeleteRowsEvent::MySQLBinLogDeleteRowsEvent ( mysql_event *pEvent, MySQLEventParser *pParser ) {
  uint64_t id;
  pParser->extractTableID ( (char *) ( pEvent + 1 ), id, pParser->getHeaderLen ( pEvent->type ) );
  MySQLTableMapEntry *table = pParser->getTable ( id );
  tables[boost::shared_ptr<SQLTable> ( new SQLTable ( new SQLIdentifier ( table->getSchema () ),
                                                      new SQLIdentifier ( table->getName () ) ) )]
    = SQLStatement::WRITE | SQLStatement::DELETE;
}

SQL::MySQLBinLogDeleteRowsEvent::~MySQLBinLogDeleteRowsEvent () {
  tables.clear ();
}

SQL::SQLStatement::table_type SQL::MySQLBinLogDeleteRowsEvent::getTables () const {
  return tables;
}
