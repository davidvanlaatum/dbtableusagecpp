//
// Created by David van Laatum on 27/3/17.
//

#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "MySQLEventParser.h"
#include "MySQLBinLogWriteRowsEvent.h"
#include "MySQLBinLogUpdateRowsEvent.h"
#include "MySQLBinLogDeleteRowsEvent.h"
#include "SQLParserContext.h"

MySQLEventParser::MySQLEventParser ( SQLParserContext *ctx ) : ctx ( ctx ) {
}

MySQLEventParser::~MySQLEventParser () {

}

void
MySQLEventParser::parse ( yy::location location, const char *data, size_t len, MySQLEventParserCallback *callback ) {
  const void *end = data + len;
  if ( ctx->getDebug () ) {
    ctx->out () << location << " Parsing " << (void *) data << " len=" << len << " " << std::endl;
  }
  mysql_event *event = (mysql_event *) data;
  do {
    std::cout << std::showbase;
    if ( ctx->getDebug () ) {
      std::cout << location << " time=" << event->timestamp << " type=" << std::hex << (int) (event->type & 0xFF)
                << " len=" << std::dec << event->len << " flags=" << std::hex << (event->flags & 0xFFFF) << std::endl;
      std::cout << std::dec;
    }

    switch ( event->type ) {
      case 0x0f:
        parse ( (mysql_format_description_event *) ( event + 1 ), event->len - sizeof ( *event ) );
        break;
      case 0x13:
        parseTableMap ( event, len );
        break;
      case 0x1E:
        callback->event ( new MySQLBinLogWriteRowsEvent ( event, this ), this );
        break;
      case 0x1F:
        callback->event ( new MySQLBinLogUpdateRowsEvent ( event, this ), this );
        break;
      case 0x20:
        callback->event ( new MySQLBinLogDeleteRowsEvent ( event, this ), this );
        break;
      default: {
        std::stringstream s;
        s << location << ": Unknown event type " << std::hex << std::showbase << (0xFF&event->type);
        throw std::runtime_error ( s.str () );
      }
    }
    event = (mysql_event *) ( ( (char *) event ) + event->len );
  } while ( event < end );
}

void MySQLEventParser::parse ( mysql_format_description_event *event, size_t len ) {
//  std::cout << event->version << std::endl << event->ver << std::endl << (int) event->len << std::endl;
  binLogVer = event->ver;
  for ( int i = 0; i < event->len; i++ ) {
    eventHeaderLengths[i + 1] = event->typeLen[i];
  }
}

char *MySQLEventParser::extractTableID ( char *data, uint64_t &id, int len ) {
  id = *(uint32_t *) data;
  data += sizeof ( uint32_t );
  id |= ( (uint64_t) ( *(uint16_t *) data ) & 0xFFFF ) << 32;
  data += sizeof ( uint16_t );
  return data;
}

void MySQLEventParser::parseTableMap ( mysql_event *event, size_t len ) {
  char *data = (char *) ( event + 1 );
  uint64_t tableId;
  extractTableID ( data, tableId, eventHeaderLengths[0x13] == 6 ? 4 : 6 );
  data += eventHeaderLengths[0x13];
  const std::string &schema = encodedString ( &data );
  const std::string &name = encodedString ( &data );
  MySQLTableMapEntry entry ( tableId, schema, name );
  if ( tableMap.find ( tableId ) != tableMap.end () && tableMap[tableId] != entry ) {
    std::cout << "Remapping " << tableId << std::endl;
  }
  tableMap[tableId] = entry;
}

void MySQLEventParser::dump () {
  for ( std::map<uint64_t, MySQLTableMapEntry>::iterator it = tableMap.begin (); it != tableMap.end (); it++ ) {
    std::cout << it->second << std::endl;
  }
}

std::string MySQLEventParser::encodedString ( char **data ) {
  char value[256] = { 0 };
  strncpy ( value, ( *data ) + 1, ( (size_t) ( *data )[0] & 0xFF ) + 1 );
  *data += 2 + (int) ( *data )[0];
  return std::string ( value );
}

uint8_t MySQLEventParser::getHeaderLen ( uint8_t type ) {
  return eventHeaderLengths[type];
}

MySQLTableMapEntry *MySQLEventParser::getTable ( uint64_t i ) {
  return &tableMap[i];
}
