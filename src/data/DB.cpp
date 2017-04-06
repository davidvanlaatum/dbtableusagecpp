//
// Created by David van Laatum on 28/3/17.
//

#include "DB.h"

DB::DB () {
  id = 0;
}

Table *DB::getTable ( std::string name ) {
  if ( tables.find ( name ) == tables.end () ) {
    changed ();
  }
  return tables[name].setName ( name );
}

DB *DB::setName ( std::string name ) {
  this->name = name;
  return this;
}

void DB::getTables ( std::list<Table *> &rt ) {
  for ( std::map<std::string, Table>::iterator it = tables.begin (); it != tables.end (); it++ ) {
    rt.push_back ( &it->second );
  }
}

const std::string &DB::getName () const {
  return name;
}

int DB::getId () const {
  return id;
}

void DB::setId ( int id ) {
  DB::id = id;
}

int DB::getHost () const {
  return host;
}

void DB::setHost ( int host ) {
  DB::host = host;
}
