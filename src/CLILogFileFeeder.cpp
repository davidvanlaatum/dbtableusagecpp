//
// Created by David van Laatum on 9/4/17.
//

#include <sys/stat.h>
#include <errno.h>
#include "CLILogFileFeeder.h"

CLILogFileFeeder::CLILogFileFeeder ( std::ostream *outputLog, std::ostream *errorLog, std::ostream *debugLog,
                                     std::ostream *progress, const boost::program_options::variables_map &vm )
  : LogFileFeeder ( outputLog, errorLog, debugLog, progress, vm ) {
  fileNum = 0;
  files = vm["input"].as<std::vector<std::string> > ();
  lastHandle = NULL;
}

FILE *CLILogFileFeeder::fileHandle () {
  lastHandle = fopen ( current->c_str (), "r" );
  if ( !lastHandle ) {
    throw std::runtime_error ( std::string ( "Failed to open file " ) + strerror ( errno ) );
  }
  return lastHandle;
}

std::string CLILogFileFeeder::fileName () {
  return *current;
}

uint64_t CLILogFileFeeder::fileSize () {
  struct stat statbuf = { 0 };
  if ( stat ( current->c_str (), &statbuf ) ) {
    throw std::runtime_error ( std::string ( "Failed to stat file " ) + strerror ( errno ) );
  }
  return (uint64_t) statbuf.st_size;
}

bool CLILogFileFeeder::next () {
  if ( lastHandle ) {
    fclose ( lastHandle );
    lastHandle = NULL;
  }
  if ( fileNum == 0 ) {
    current = files.begin ();
  } else {
    current++;
  }
  fileNum++;
  return current != files.end ();
}

void CLILogFileFeeder::init ( const Host *pHost ) {

}
