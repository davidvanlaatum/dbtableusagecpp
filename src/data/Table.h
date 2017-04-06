//
// Created by David van Laatum on 28/3/17.
//

#ifndef DBTABLEUSAGECPP_TABLE_H
#define DBTABLEUSAGECPP_TABLE_H

#include <string>
#include <soci.h>
#include "DBObject.h"

class Table : public DBObject {
public:
    Table ();
    Table *setName ( std::string name );
    const std::string &getName () const;
    int getId () const;
    void setId ( int id );

    void updateWrite ( time_t i );
    void updateRead ( time_t i );
    void updateInsert ( time_t i );
    void updateUpdate ( time_t i );
    void updateDelete ( time_t i );
    void updateAlter ( time_t i );
    time_t getLastWrite () const;
    time_t getLastRead () const;
    time_t getCreated () const;
    time_t getLastInsert () const;
    time_t getLastUpdate () const;
    time_t getLastDelete () const;
    time_t getLastAlter () const;
    void setLastWrite ( time_t lastWrite );
    void setLastRead ( time_t lastRead );
    void setLastInsert ( time_t lastInsert );
    void setLastUpdate ( time_t lastUpdate );
    void setLastDelete ( time_t lastDelete );
    void setLastAlter ( time_t lastAlter );
    void setCreated ( time_t created );
    int getDatabase () const;
    void setDatabase ( int database );
private:
    int id;
    std::string name;
    int database;
    time_t lastWrite;
    time_t lastRead;
    time_t lastInsert;
    time_t lastUpdate;
    time_t lastDelete;
    time_t lastAlter;
    time_t created;
};
namespace soci {
  template<>
  struct type_conversion<Table> {
      typedef values base_type;

      static void from_base ( values const &v, indicator i, Table &p ) {
        if ( i == i_ok ) {
          p.setId ( v.get<int> ( "ID" ) );
          p.setName ( v.get<> ( "NAME", std::string () ) );
          p.setDatabase ( v.get<int> ( "DATABASE" ) );
          p.setCreated ( v.get < long
          long > ( "CREATED", 0 ) );
          p.setLastWrite ( v.get < long
          long > ( "WRITE", 0 ) );
          p.setLastRead ( v.get < long
          long > ( "READ", 0 ) );
          p.setLastInsert ( v.get < long
          long > ( "INSERT", 0 ) );
          p.setLastUpdate ( v.get < long
          long > ( "UPDATE", 0 ) );
          p.setLastDelete ( v.get < long
          long > ( "DELETE", 0 ) );
          p.setLastAlter ( v.get < long
          long > ( "ALTER", 0 ) );
        }
      }

      static void to_base ( const Table &p, values &v, indicator &ind ) {
        v.set<int> ( "ID", p.getId () );
        v.set ( "NAME", p.getName () );
        v.set<int> ( "DATABASE", p.getDatabase () );
        v.set < long
        long > ( "CREATED", p.getCreated (), p.getCreated () == 0 ? i_null : i_ok );
        v.set < long
        long > ( "WRITE", p.getLastWrite (), p.getLastWrite () == 0 ? i_null : i_ok );
        v.set < long
        long > ( "READ", p.getLastRead (), p.getLastRead () == 0 ? i_null : i_ok );
        v.set < long
        long > ( "INSERT", p.getLastInsert (), p.getLastInsert () == 0 ? i_null : i_ok );
        v.set < long
        long > ( "UPDATE", p.getLastUpdate (), p.getLastUpdate () == 0 ? i_null : i_ok );
        v.set < long
        long > ( "DELETE", p.getLastDelete (), p.getLastDelete () == 0 ? i_null : i_ok );
        v.set < long
        long > ( "ALTER", p.getLastAlter (), p.getLastAlter () == 0 ? i_null : i_ok );
        ind = i_ok;
      }
  };
}

#endif //DBTABLEUSAGECPP_TABLE_H
