//
// Created by David van Laatum on 9/4/17.
//

#include <soci.h>
#include "MySQLBinLogFileFeeder.h"

MySQLBinLogFileFeeder::MySQLBinLogFileFeeder ( std::ostream *outputLog, std::ostream *errorLog,
                                               std::ostream *debugLog, std::ostream *progress,
                                               boost::program_options::variables_map &vm )
  : LogFileFeeder ( outputLog, errorLog, debugLog, progress, vm ) {
  if ( !vm.count ( "monitor.host" ) ) {
    throw std::runtime_error ( "monitor.host is required" );
  }
  if ( !vm.count ( "monitor.user" ) ) {
    throw std::runtime_error ( "monitor.user is required" );
  }
  if ( !vm.count ( "storage.url" ) ) {
    throw std::runtime_error ( "storage.url is required" );
  }
  host = vm["monitor.host"].as<std::string> ();
  user = vm["monitor.user"].as<std::string> ();
  password = vm["monitor.password"].as<std::string> ();
  fileNum = 0;
  initalOffset = 0;
  lastHandle = NULL;
}

FILE *MySQLBinLogFileFeeder::fileHandle () {
  std::stringstream command;
  command << "mysqlbinlog -h" + host + " -R -u " + user + " -p" + password + " " + current->first;
  if ( initalOffset ) {
    command << " --start-position=" << initalOffset;
    initalOffset = 0;
  }
  lastHandle = popen ( command.str ().c_str (), "r" );
  return lastHandle;
}

std::string MySQLBinLogFileFeeder::fileName () {
  return current->first;
}

bool MySQLBinLogFileFeeder::next () {
  if ( lastHandle ) {
    int exitcode = pclose ( lastHandle );
    lastHandle = NULL;
    if ( exitcode ) {
      *errorLog << "mysqlbinlog exited with " << exitcode << std::endl;
      return false;
    }
  }
  if ( fileNum == 0 ) {
    current = logFiles.begin ();
  } else {
    current++;
  }
  fileNum++;
  return current != logFiles.end ();
}

void MySQLBinLogFileFeeder::init ( const Host *pHost ) {
  session sql;
  try {
    sql.open ( "mysql://host=" + host + " user=" + user + " password=" + password );

    rowset<row> rs = ( sql.prepare << "SHOW MASTER LOGS" );

    for ( rowset<row>::const_iterator it = rs.begin (); it != rs.end (); ++it ) {
      if ( pHost && !pHost->getLastLogFile ().empty () && pHost->getLastLogFile () == it->get<std::string> ( 0 ) ) {
        logFiles.clear ();
        initalOffset = pHost->getLastLogPos ();
      }
      switch ( it->get_properties ( 1 ).get_data_type () ) {
        case dt_integer:
          logFiles[it->get<std::string> ( 0 )] = (size_t) it->get<int> ( 1 );
          break;
        case dt_long_long:
          logFiles[it->get<std::string> ( 0 )] = (size_t) it->get < long
          long > ( 1 );
          break;
        case dt_unsigned_long_long:
          logFiles[it->get<std::string> ( 0 )] = (size_t) it->get < unsigned
          long
          long > ( 1 );
          break;
      }
    }

    sql.close ();
  } catch ( ... ) {
    sql.close ();
    throw;
  }
}

uint64_t MySQLBinLogFileFeeder::fileSize () {
  return current->second;
}

std::string MySQLBinLogFileFeeder::progressText () {
  std::stringstream s;
  s << LogFileFeeder::progressText () << " " << fileNum << " of " << logFiles.size ();
  return s.str ();
}
