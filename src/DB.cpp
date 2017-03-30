//
// Created by David van Laatum on 28/3/17.
//

#include "DB.h"

Table *DB::getTable ( std::string name ) {
  return tables[name].setName ( name );
}

DB *DB::setName ( std::string name ) {
  this->name = name;
  return this;
}

std::list<Table *> DB::getTables () {
  std::list<Table *> rt;

  for ( auto it = tables.begin (); it != tables.end (); it++ ) {
    rt.push_back ( &it->second );
  }

  return rt;
}

const std::string &DB::getName () const {
  return name;
}
