//
// Created by David van Laatum on 9/4/17.
//

#include <DataCollector.h>
#include <SQLParserContext.h>
#include <boost/program_options/variables_map.hpp>
#include "LogFileFeeder.h"

LogFileFeeder::LogFileFeeder ( std::ostream *outputLog, std::ostream *errorLog, std::ostream *debugLog,
                               std::ostream *progress, const boost::program_options::variables_map &vm ) :
  outputLog ( outputLog ), errorLog ( errorLog ), debugLog ( debugLog ), progress ( progress ), vm ( vm ) {

}

int LogFileFeeder::feed ( DataCollector *collector ) {
  init ( collector->getHost () );

  if (next ()) {
    do {
      FILE *handle = fileHandle ();
      *progress << "Now reading " << progressText () << std::endl;
      collector->setCurrentFileSize ( fileSize () );
      SQL::SQLParserContext context ( collector );
      setupContext ( context );
      context.parseFileHandle ( handle, fileName () );
      collector->endOfFile ( &context );
    } while ( next () );
  } else {
    *errorLog << "Nothing to do" << std::endl;
  }

  return 0;
}

void LogFileFeeder::setupContext ( SQL::SQLParserContext &context ) {
  context.setDebugStream ( debugLog );
  context.setErrorStream ( errorLog );
  context.setOutStream ( outputLog );
  context.setDebug ( vm["debug"].as<int> () );
  context.setVerbose ( vm["verbose"].as<int> () );
  if ( vm.count ( "monitor.ignoredb" ) ) {
    std::vector<std::string> ignoredb = vm["monitor.ignoredb"].as<std::vector<std::string> > ();
    for ( std::vector<std::string>::iterator it = ignoredb.begin (); it != ignoredb.end (); ++it ) {
      context.addIgnoreDB ( *it );
    }
  }
}

std::string LogFileFeeder::progressText () {
  return fileName ();
}
