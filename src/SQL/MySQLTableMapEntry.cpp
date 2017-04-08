//
// Created by David van Laatum on 27/3/17.
//

#include <iomanip>
#include "MySQLTableMapEntry.h"

SQL::MySQLTableMapEntry::MySQLTableMapEntry ( uint64_t id, std::string schema, std::string name ) : id ( id ),
                                                                                               schema ( schema ),
                                                                                               name ( name ) {
}

SQL::MySQLTableMapEntry::MySQLTableMapEntry () {

}

const std::string &SQL::MySQLTableMapEntry::getSchema () const {
  return schema;
}

const std::string &SQL::MySQLTableMapEntry::getName () const {
  return name;
}

bool SQL::MySQLTableMapEntry::operator== ( const MySQLTableMapEntry &rhs ) const {
  return schema == rhs.schema && name == rhs.name;
}

bool SQL::MySQLTableMapEntry::operator!= ( const MySQLTableMapEntry &rhs ) const {
  return !( rhs == *this );
}
namespace SQL {
  std::ostream &operator<< ( std::ostream &os, const SQL::MySQLTableMapEntry &entry ) {
    os << std::setiosflags ( std::ios::left )
       << "id: " << entry.id
       << " schema: " << std::setw ( 32 ) << entry.schema
       << " name: " << std::setw ( 32 ) << entry.name;
    return os;
  }
}
