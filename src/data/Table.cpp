//
// Created by David van Laatum on 28/3/17.
//

#include "Table.h"

Table::Table () {
  id = 0;
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
    changed ();
  }
}

void Table::updateWrite ( time_t i ) {
  if ( i > lastWrite ) {
    lastWrite = i;
    changed ();
  }
}

void Table::updateInsert ( time_t i ) {
  if ( i > lastInsert ) {
    lastInsert = i;
    changed ();
  }
}

void Table::updateUpdate ( time_t i ) {
  if ( i > lastUpdate ) {
    lastUpdate = i;
    changed ();
  }
}

void Table::updateDelete ( time_t i ) {
  if ( i > lastDelete ) {
    lastDelete = i;
    changed ();
  }
}

void Table::updateAlter ( time_t i ) {
  if ( i > lastAlter ) {
    lastAlter = i;
    changed ();
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

int Table::getId () const {
  return id;
}

void Table::setId ( int id ) {
  Table::id = id;
}

void Table::setLastWrite ( time_t lastWrite ) {
  Table::lastWrite = lastWrite;
}

void Table::setLastRead ( time_t lastRead ) {
  Table::lastRead = lastRead;
}

void Table::setLastInsert ( time_t lastInsert ) {
  Table::lastInsert = lastInsert;
}

void Table::setLastUpdate ( time_t lastUpdate ) {
  Table::lastUpdate = lastUpdate;
}

void Table::setLastDelete ( time_t lastDelete ) {
  Table::lastDelete = lastDelete;
}

void Table::setLastAlter ( time_t lastAlter ) {
  Table::lastAlter = lastAlter;
}

void Table::setCreated ( time_t created ) {
  Table::created = created;
}

int Table::getDatabase () const {
  return database;
}

void Table::setDatabase ( int database ) {
  Table::database = database;
}

void Table::updateCreated ( time_t i ) {
  if ( i > created) {
    created = i;
    changed ();
  }
}
