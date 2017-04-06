//
// Created by David van Laatum on 28/3/17.
//

#include "Host.h"

Host::Host ( const std::string &name ) : name ( name ) {
  id = 0;
  changed ();
}

Host::Host () {
  id = 0;
}

DB *Host::getDB ( std::string name ) {
  if ( dbs.find ( name ) == dbs.end () ) {
    changed ();
  }
  return dbs[name].setName ( name );
}

void Host::getDBs ( std::list<DB *> &rt ) {
  for ( std::map<std::string, DB>::const_iterator it = dbs.begin (); it != dbs.end (); it++ ) {
    DB *db = &dbs.at ( it->first );
    rt.push_back ( db );
  }
}

const std::string &Host::getName () const {
  return name;
}

void Host::setName ( const std::string &name ) {
  changed ();
  Host::name = name;
}

int Host::getId () const {
  return id;
}

void Host::setId ( int id ) {
  Host::id = id;
}

const std::string &Host::getLastLogFile () const {
  return lastLogFile;
}

void Host::setLastLogFile ( const std::string &lastLogFile ) {
  changed ();
  Host::lastLogFile = lastLogFile;
}

int Host::getLastLogPos () const {
  return lastLogPos;
}

void Host::setLastLogPos ( int lastLogPos ) {
  changed ();
  Host::lastLogPos = lastLogPos;
}
