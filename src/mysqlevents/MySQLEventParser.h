//
// Created by David van Laatum on 27/3/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLEVENTPARSER_H
#define DBTABLEUSAGECPP_MYSQLEVENTPARSER_H

#include <cstdio>
#include <map>
#include "events.h"
#include "MySQLTableMapEntry.h"
#include "../location.hh"

class MySQLEventParser {
public:
    void parse ( yy::location location, const char *data, size_t len );
    void dump ();
protected:
    void parse ( mysql_format_description_event *event, size_t len );
    void parseTableMap ( mysql_event *event, size_t len );
    char *extractTableID ( char *data, uint64_t &id, int len );
    std::string encodedString(char **data);

    std::map<uint8_t, uint8_t> eventHeaderLengths;
    std::map<uint64_t, MySQLTableMapEntry> tableMap;
    uint16_t binLogVer;
};


#endif //DBTABLEUSAGECPP_MYSQLEVENTPARSER_H
