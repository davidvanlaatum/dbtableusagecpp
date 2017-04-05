//
// Created by David van Laatum on 27/3/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLTABLEMAPENTRY_H
#define DBTABLEUSAGECPP_MYSQLTABLEMAPENTRY_H


#include <string>
#include <ostream>
#include <stdint.h>

class MySQLTableMapEntry {
public:
    MySQLTableMapEntry ( uint64_t id, std::string schema, std::string name );
    MySQLTableMapEntry ();

    const std::string &getSchema () const;
    const std::string &getName () const;
    bool operator== ( const MySQLTableMapEntry &rhs ) const;
    bool operator!= ( const MySQLTableMapEntry &rhs ) const;
    friend std::ostream &operator<< ( std::ostream &os, const MySQLTableMapEntry &entry );
private:
    uint64_t id;
    std::string schema;
    std::string name;
};


#endif //DBTABLEUSAGECPP_MYSQLTABLEMAPENTRY_H
