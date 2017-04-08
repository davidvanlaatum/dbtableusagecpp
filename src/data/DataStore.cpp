//
// Created by David van Laatum on 6/4/17.
//

#include <iostream>
#include "DataStore.h"

DataStore::DataStore () {
}

DataStore::~DataStore () {
  sql.close ();
}

void DataStore::setConnection ( std::string url ) {
  sql.open ( url );
  sql.uppercase_column_names ( true );
//  sql.set_log_stream ( &std::cout );
}

bool DataStore::load ( Host &host, std::string name ) {
  sql << "select * from host where name = :NAME", use ( name ), into ( host );
  bool rt = sql.got_data ();

  DB db;
  statement dbs = ( sql.prepare << "select * from db where host = :ID", use ( host ), into ( db ) );
  dbs.execute ();
  while ( dbs.fetch () ) {
    std::cout << "Loading DB " << db.getName () << " with id " << db.getId () << std::endl;
    DB *pDB = host.getDB ( db.getName () );
    *pDB = db;

    Table table;
    statement tables = ( sql.prepare << "select * from tables where `database` = :ID", use ( db ),
      into ( table ) );
    tables.execute ();
    while ( tables.fetch () ) {
      Table *pTable = pDB->getTable ( table.getName () );
      *pTable = table;
      std::cout << "Loaded table " << db.getName () << "." << pTable->getName () << " with id " << pTable->getId () <<
                std::endl;
      pTable->clearChanged ();
    }
    pDB->clearChanged ();
  }

  return rt;
}

void DataStore::save ( Host &host ) {
  saveCount = 0;
  transaction tr ( sql );
  if ( host.hasChanged () ) {
    saveCount++;
    if ( host.getId () != 0 ) {
      sql << "update host set name = :NAME, last_log_file = :LAST_LOG_FILE, last_log_pos = :LAST_LOG_POS where id = "
        ":ID", use ( host );
    } else {
      sql << "insert into host (name,last_log_file,last_log_pos) VALUES(:NAME,:LAST_LOG_FILE,:LAST_LOG_POS)",
        use ( host );
      long id;
      if ( sql.get_last_insert_id ( "host", id ) ) {
        host.setId ( (int) id );
      } else {
        sql << "select * from host where name = :1", use ( host.getName () ), into ( host );
      }
      if ( host.getId () == 0 ) {
        throw std::runtime_error ( "Failed to get id for host " + host.getName () );
      }
      std::cout << "Host " << host.getName () << " got id " << host.getId () << std::endl;
    }
  }
  std::list<DB *> dbs;
  host.getDBs ( dbs );
  for ( std::list<DB *>::iterator it = dbs.begin (); it != dbs.end (); ++it ) {
    save ( **it, host.getId () );
  }
  host.clearChanged ();
  tr.commit ();
}

void DataStore::save ( Table &table, int db ) {
  if ( table.hasChanged () ) {
    saveCount++;
    table.setDatabase ( db );
    if ( table.getId () != 0 ) {
      sql
        << "update tables set name = :NAME,created = :CREATED,`read` = :READ,`write` = :WRITE,`insert` = :INSERT, `update` "
          "= :UPDATE,`delete` = :DELETE, `alter` = :ALTER where id = :ID", use (
        table );
    } else {
      sql << "insert into tables (name,`database`,created,`read`,`write`,`insert`,`update`,`delete`,`alter`) "
        "VALUES (:NAME,:DATABASE,:CREATED,:READ,:WRITE,:INSERT,:UPDATE,:DELETE,:ALTER)", use ( table );
      long id = 0;
      if ( sql.get_last_insert_id ( "table", id ) ) {
        table.setId ( (int) id );
      } else {
        sql << "select ID from tables where name = :1 and `database` = :2", use ( table.getName () ),
          use ( db ), into ( id );
        table.setId ( id );
      }
      if ( table.getId () == 0 ) {
        throw std::runtime_error ( "Failed to get id for table " + table.getName () );
      }
    }
    table.clearChanged ();
  }
}

void DataStore::save ( DB &db, int host ) {
  if ( db.hasChanged () ) {
    saveCount++;
    db.setHost ( host );
    if ( db.getId () != 0 ) {
      sql << "update db set name = :NAME where id = :ID", use ( db );
    } else {
      sql << "insert into db (name,host) VALUES(:NAME,:HOST)", use ( db );
      long id;
      if ( sql.get_last_insert_id ( "db", id ) ) {
        db.setId ( (int) id );
      } else {
        sql << "select * from db where name = :1 and host = :2", use ( db.getName () ), use ( db.getHost () ),
          into ( db );
      }
      if ( db.getId () == 0 ) {
        throw std::runtime_error ( "Failed to get id for db " + db.getName () );
      }
    }
  }
  std::list<Table *> tables;
  db.getTables ( tables );
  for ( std::list<Table *>::iterator it = tables.begin (); it != tables.end (); ++it ) {
    save ( **it, db.getId () );
  }
  db.clearChanged ();
}

size_t DataStore::getSaveCount () const {
  return saveCount;
}
