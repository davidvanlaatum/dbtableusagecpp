//
// Created by David van Laatum on 9/4/17.
//

#include <soci.h>
#include <boost/date_time.hpp>
#include "Host.h"
#include "MySQLPrePopulater.h"

using namespace soci;

MySQLPrePopulater::MySQLPrePopulater ( std::string host, std::string user, std::string pass ) : host ( host ),
                                                                                                user ( user ),
                                                                                                pass ( pass ) {
}

void MySQLPrePopulater::populate ( Host *pHost ) {
  session sql;
  try {
    sql.open ( "mysql://host=" + host + " user=" + user + " password=" + pass );

    rowset<row> rs = ( sql.prepare << "SELECT\n"
      "\tTABLE_SCHEMA ,\n"
      "\tTABLE_NAME,\n"
      "\tCREATE_TIME\n"
      "FROM\n"
      "\t`information_schema`.`tables`\n"
      "WHERE\n"
      "\ttable_type = 'BASE TABLE' AND table_schema NOT IN('PERFORMANCE_SCHEMA','mysql');" );

    boost::local_time::local_time_input_facet timeParser;
    timeParser.set_iso_format ();

    for ( rowset<row>::const_iterator it = rs.begin (); it != rs.end (); ++it ) {
      Table *pTable = pHost->getDB ( it->get<std::string> ( 0 ) )->getTable ( it->get<std::string> ( 1 ) );
      tm tm = it->get<std::tm> ( 2 );
      pTable->updateCreated ( mktime ( &tm ) );
    }

    sql.close ();
  } catch ( ... ) {
    sql.close ();
    throw;
  }
}
