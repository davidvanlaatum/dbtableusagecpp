//
// Created by David van Laatum on 5/4/17.
//

#include <stdio.h>
#include <iostream>
#include "LogFileFetcher.h"

void LogFileFetcher::setConnection ( std::string host, std::string user, std::string password ) {
  this->host = host;
  this->user = user;
  this->password = password;
}

bool LogFileFetcher::fetchLogs () {
  sql.open ( "mysql://host=" + host + " user=" + user + " password=" + password );

  rowset<row> rs = ( sql.prepare << "SHOW MASTER LOGS" );

  for ( rowset<row>::const_iterator it = rs.begin (); it != rs.end (); ++it ) {
    logFiles.push_back ( ( *it ).get<std::string> ( 0 ) );
  }

  current = logFiles.begin ();
  return true;
}

std::string LogFileFetcher::currentLogFile () {
  return *current;
}

bool LogFileFetcher::hasMoreLogs () {
  return current != logFiles.end ();
}

FILE *LogFileFetcher::fileHandle () {
  std::string command = "mysqlbinlog -h" + host + " -R -u " + user + " -p" + password + " " + *current;
  return popen ( command.c_str (), "r" );
}

void LogFileFetcher::next () {
  current++;
}
