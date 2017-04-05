//
// Created by David van Laatum on 28/3/17.
//

#include "Host.h"

DB *Host::getDB ( std::string name ) {
  return dbs[name].setName ( name );
}

void Host::getDBs ( std::list<DB *> &rt ) {
  for ( std::map<std::string, DB>::const_iterator it = dbs.begin (); it != dbs.end (); it++ ) {
    DB *db = &dbs.at ( it->first );
    rt.push_back ( db );
  }
}
