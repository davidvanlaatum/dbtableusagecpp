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

void DB::getTables (std::list<Table *> &rt) {
  for ( std::map<std::string,Table>::iterator it = tables.begin (); it != tables.end (); it++ ) {
    rt.push_back ( &it->second );
  }
}

const std::string &DB::getName () const {
  return name;
}
