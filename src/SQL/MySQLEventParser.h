//
// Created by David van Laatum on 27/3/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLEVENTPARSER_H
#define DBTABLEUSAGECPP_MYSQLEVENTPARSER_H

#include <cstdio>
#include <map>
#include "MySQLEvents.h"
#include "MySQLTableMapEntry.h"
#include "location.hh"
namespace SQL {
  class MySQLEventParserCallback;
  class MySQLBinLogEvent;
  class SQLParserContext;

  class MySQLEventParser {
  public:
      MySQLEventParser ( SQLParserContext *ctx );
      virtual ~MySQLEventParser ();
      void parse ( yy::location location, const char *data, size_t len, MySQLEventParserCallback *callback );
      void dump ();
      char *extractTableID ( char *data, uint64_t &id, int len );
      uint8_t getHeaderLen ( uint8_t type );
      MySQLTableMapEntry *getTable ( uint64_t i );
  protected:
      void parse ( mysql_format_description_event *event, size_t len );
      void parseTableMap ( mysql_event *event, size_t len );
      std::string encodedString ( char **data );

      std::map<uint8_t, uint8_t> eventHeaderLengths;
      std::map<uint64_t, MySQLTableMapEntry> tableMap;
      uint16_t binLogVer;
      SQLParserContext *ctx;
  };

  class MySQLEventParserCallback {
  public:
      virtual void event ( MySQLBinLogEvent *event, MySQLEventParser *parser ) = 0;
  };
}

#endif //DBTABLEUSAGECPP_MYSQLEVENTPARSER_H
