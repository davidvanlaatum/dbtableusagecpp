//
// Created by David van Laatum on 28/3/17.
//

#include "Table.h"

Table::Table () {
  lastRead = 0;
  lastWrite = 0;
  lastInsert = 0;
  lastUpdate = 0;
  lastDelete = 0;
  lastAlter = 0;
  created = 0;
}

Table *Table::setName ( std::string name ) {
  this->name = name;
  return this;
}

const std::string &Table::getName () const {
  return name;
}

void Table::updateRead ( time_t i ) {
  if ( i > lastRead ) {
    lastRead = i;
  }
}

void Table::updateWrite ( time_t i ) {
  if ( i > lastWrite ) {
    lastWrite = i;
  }
}

void Table::updateInsert ( time_t i ) {
  if ( i > lastInsert ) {
    lastInsert = i;
  }
}

void Table::updateUpdate ( time_t i ) {
  if ( i > lastUpdate ) {
    lastUpdate = i;
  }
}

void Table::updateDelete ( time_t i ) {
  if ( i > lastDelete ) {
    lastDelete = i;
  }
}

void Table::updateAlter ( time_t i ) {
  if ( i > lastAlter ) {
    lastAlter = i;
  }
}

time_t Table::getLastWrite () const {
  return lastWrite;
}

time_t Table::getLastRead () const {
  return lastRead;
}

time_t Table::getCreated () const {
  return created;
}

time_t Table::getLastInsert () const {
  return lastInsert;
}

time_t Table::getLastUpdate () const {
  return lastUpdate;
}

time_t Table::getLastDelete () const {
  return lastDelete;
}

time_t Table::getLastAlter () const {
  return lastAlter;
}
