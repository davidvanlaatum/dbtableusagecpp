//
// Created by David van Laatum on 28/3/17.
//

#ifndef DBTABLEUSAGECPP_HOST_H
#define DBTABLEUSAGECPP_HOST_H

#include <string>
#include <map>
#include <list>
#include <boost/scoped_ptr.hpp>
#include <soci.h>
#include "DB.h"
#include "DBObject.h"

class Host : public DBObject {
public:
    Host ( const std::string &name );
    Host ();
    const std::string &getName () const;
    void setName ( const std::string &name );
    DB *getDB ( std::string name );
    void getDBs ( std::list<DB *> &rt );
    int getId () const;
    void setId ( int id );
    const std::string &getLastLogFile () const;
    void setLastLogFile ( const std::string &lastLogFile );
    int getLastLogPos () const;
    void setLastLogPos ( int lastLogPos );
private:
    int id;
    std::map<std::string, DB> dbs;
    std::string name;
    std::string lastLogFile;
    int lastLogPos;
};

namespace soci {
  template<>
  struct type_conversion<Host> {
      typedef values base_type;

      static void from_base ( values const &v, indicator i, Host &p ) {
        if ( i == i_ok ) {
          try {
            p.setId ( v.get<int> ( "ID", p.getId () ) );
            p.setName ( v.get<> ( "NAME", std::string () ) );
            p.setLastLogFile ( v.get<> ( "LAST_LOG_FILE", std::string () ) );
            p.setLastLogPos ( v.get<int> ( "LAST_LOG_POS", 0 ) );
          } catch ( std::bad_cast &e ) {
            std::cerr << "Bad cast in host from_base" << std::endl;
            throw;
          }
        }
      }

      static void to_base ( const Host &p, values &v, indicator &ind ) {
        try {
          v.set<int> ( "ID", p.getId () );
          v.set ( "NAME", p.getName () );
          v.set ( "LAST_LOG_FILE", p.getLastLogFile (), p.getLastLogFile ().empty () ? i_null : i_ok );
          v.set<int> ( "LAST_LOG_POS", p.getLastLogPos (), p.getLastLogPos () == 0 ? i_null : i_ok );
          ind = i_ok;
        } catch ( std::bad_cast &e ) {
          std::cerr << "Bad cast in host to_base" << std::endl;
          throw;
        }
      }
  };
}

#endif //DBTABLEUSAGECPP_HOST_H
