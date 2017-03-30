//
// Created by David van Laatum on 27/3/17.
//

#ifndef DBTABLEUSAGECPP_EVENTS_H
#define DBTABLEUSAGECPP_EVENTS_H

#include <stdint.h>

struct mysql_event {
    int32_t timestamp;
    uint8_t type;
    uint32_t serverId;
    uint32_t len;
    uint32_t next;
    uint16_t flags;
} __attribute__((packed));

struct mysql_format_description_event {
    uint16_t ver;
    char version[50];
    int32_t timestamp;
    uint8_t len;
    uint8_t typeLen[1];
} __attribute__((packed));

#endif //DBTABLEUSAGECPP_EVENTS_H
