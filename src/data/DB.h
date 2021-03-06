//
// Created by David van Laatum on 28/3/17.
//

#ifndef DBTABLEUSAGECPP_DB_H
#define DBTABLEUSAGECPP_DB_H

#include <string>
#include <map>
#include <list>
#include <soci.h>
#include "Table.h"
#include "DBObject.h"

class DB : public DBObject {
public:
    DB ();
    Table *getTable ( std::string name );
    DB *setName ( std::string name );
    const std::string &getName () const;
    void getTables ( std::list<Table *> &rt );
    int getId () const;
    void setId ( int id );
    int getHost () const;
    void setHost ( int host );
private:
    int id;
    int host;
    std::string name;
    std::map<std::string, Table> tables;
};

namespace soci {
  template<>
  struct type_conversion<DB> {
      typedef values base_type;

      static void from_base ( values const &v, indicator i, DB &p ) {
        if ( i == i_ok ) {
          try {
            p.setId ( v.get<> ( "ID", 0 ) );
            p.setHost ( v.get<> ( "HOST", 0 ) );
            p.setName ( v.get<> ( "NAME", std::string () ) );
          } catch ( std::bad_cast &e ) {
            throw std::runtime_error("Bad cast in host from_base");
            throw;
          }
        }
      }

      static void to_base ( const DB &p, values &v, indicator &ind ) {
        try {
          v.set ( "ID", p.getId () );
          v.set ( "HOST", p.getHost () );
          v.set ( "NAME", p.getName () );
          ind = i_ok;
        } catch ( std::bad_cast &e ) {
          throw std::runtime_error("Bad cast in host to_base");
        }
      }
  };
}

#endif //DBTABLEUSAGECPP_DB_H
