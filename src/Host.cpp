//
// Created by David van Laatum on 28/3/17.
//

#include "Host.h"

DB *Host::getDB ( std::string name ) {
  return dbs[name].setName ( name );
}

std::list<DB *> Host::getDBs () {
  std::list<DB *> rt ( dbs.size () );
  for ( auto it = dbs.begin (); it != dbs.end (); it++ ) {
    rt.push_back ( &it->second );
  }
  return rt;
}
