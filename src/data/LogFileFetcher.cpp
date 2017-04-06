//
// Created by David van Laatum on 5/4/17.
//

#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include "LogFileFetcher.h"

void LogFileFetcher::setConnection ( std::string host, std::string user, std::string password ) {
  this->host = host;
  this->user = user;
  this->password = password;
}

bool LogFileFetcher::fetchLogs ( const Host *pHost ) {
  try {
    sql.open ( "mysql://host=" + host + " user=" + user + " password=" + password );

    rowset<row> rs = ( sql.prepare << "SHOW MASTER LOGS" );

    for ( rowset<row>::const_iterator it = rs.begin (); it != rs.end (); ++it ) {
      if ( pHost && !pHost->getLastLogFile ().empty () && pHost->getLastLogFile () == it->get<std::string> ( 0 ) ) {
        logFiles.clear ();
      }
      switch ( it->get_properties ( 1 ).get_data_type () ) {
        case dt_integer:
          logFiles[it->get<std::string> ( 0 )] = (size_t) it->get<int> ( 1 );
          break;
        case dt_long_long:
          logFiles[it->get<std::string> ( 0 )] = (size_t) it->get <long long> ( 1 );
          break;
        case dt_unsigned_long_long:
          logFiles[it->get<std::string> ( 0 )] = (size_t) it->get<unsigned long long> ( 1 );
          break;
      }
    }

    current = logFiles.begin ();

    sql.close ();
  } catch ( ... ) {
    sql.close ();
    throw;
  }
  return true;
}

std::string LogFileFetcher::currentLogFile () {
  return current->first;
}

bool LogFileFetcher::hasMoreLogs () {
  return current != logFiles.end ();
}

FILE *LogFileFetcher::fileHandle () {
  std::string command = "mysqlbinlog -h" + host + " -R -u " + user + " -p" + password + " " + current->first;
  return popen ( command.c_str (), "r" );
}

void LogFileFetcher::next () {
  current++;
}

uint64_t LogFileFetcher::currentLogFileSize () {
  return current->second;
}
