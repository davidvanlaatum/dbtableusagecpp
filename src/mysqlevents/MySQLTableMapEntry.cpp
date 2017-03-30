//
// Created by David van Laatum on 27/3/17.
//

#include <iomanip>
#include "MySQLTableMapEntry.h"

MySQLTableMapEntry::MySQLTableMapEntry ( uint64_t id, std::string schema, std::string name ) : id ( id ),
                                                                                               schema ( schema ),
                                                                                               name ( name ) {
}

MySQLTableMapEntry::MySQLTableMapEntry () {

}

const std::string &MySQLTableMapEntry::getSchema () const {
  return schema;
}

const std::string &MySQLTableMapEntry::getName () const {
  return name;
}

bool MySQLTableMapEntry::operator== ( const MySQLTableMapEntry &rhs ) const {
  return schema == rhs.schema && name == rhs.name;
}

bool MySQLTableMapEntry::operator!= ( const MySQLTableMapEntry &rhs ) const {
  return !( rhs == *this );
}

std::ostream &operator<< ( std::ostream &os, const MySQLTableMapEntry &entry ) {
  os << std::setiosflags ( std::ios::left )
     << "id: " << entry.id
     << " schema: " << std::setw ( 32 ) << entry.schema
     << " name: " << std::setw ( 32 ) << entry.name;
  return os;
}
