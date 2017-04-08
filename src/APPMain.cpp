//
// Created by David van Laatum on 31/3/17.
//

#include <boost/filesystem.hpp>
#include "appversion.h"
#include <iostream>
#include <stdio.h>
#include <DataStore.h>
#include "APPMain.h"
#include "SQL/SQLParserContext.h"
#include "data/DataCollector.h"
#include "LogFileFetcher.h"
namespace po = boost::program_options;
namespace fs = boost::filesystem;

std::ostream &operator<< ( std::ostream &os, const po::variable_value &value ) {
  if ( value.value ().type () == typeid ( int ) ) {
    os << value.as<int> ();
  } else if ( value.value ().type () == typeid ( std::string ) ) {
    os << value.as<std::string> ();
  } else if ( value.value ().type () == typeid ( bool ) ) {
    os << ( value.as<bool> () ? "true" : "false" );
  } else {
    os << value.value ().type ().name ();
  }
  return os;
}

APPMain::APPMain () : options ( "options" ), config ( "config" ) {
  options.add_options ()
           ( "help,h", po::bool_switch (), "produce help message" )
           ( "version,V", po::bool_switch (), "version" )
           ( "dump", po::bool_switch (), "dump settings" )
           ( "print", po::bool_switch (), "print usage at end" )
#ifdef HAVE_PARSE_CONFIG_FILE
           ( "config,c", po::value<std::string> ()->default_value ( "config.ini" ), "config file" )
#endif
           ( "input", po::value<std::string> (), "local file to read" );
  config.add_options ()
          ( "debug,d", po::value<int> ()->default_value ( 0 )->implicit_value ( 1 ), "Set debugging level" )
          ( "verbose,v", po::value<int> ()->default_value ( 0 )->implicit_value ( 1 ), "verbose mode" )
          ( "storage.url", po::value<std::string> (), "URL of database to store results in" )
          ( "storage.user", po::value<std::string> (), "Username to connect with" )
          ( "storage.password", po::value<std::string> (), "password to connect with" )
          ( "storage.commit", po::value<unsigned> ()->default_value ( 10 ), "Commit to database interval" )
          ( "monitor.host", po::value<std::string> (), "hostname to connect to for logs" )
          ( "monitor.user", po::value<std::string> (), "Username to connect with" )
          ( "monitor.password", po::value<std::string> ()->default_value ( "" ), "password to connect with" )
          ( "monitor.ignoredb", po::value<std::vector<std::string> > ()->multitoken ()->composing (), "ignore "
            "databases" );
  options.add ( config );
}

int APPMain::main ( int argc, char *argv[] ) {
  int exit = 0;
  po::variables_map vm;
  try {
    po::positional_options_description p;
    p.add ( "input", -1 );
    po::store ( po::command_line_parser ( argc, argv ).options ( options ).positional ( p ).run (), vm );
    parseConfig ( vm );
    po::notify ( vm );
    if ( vm["help"].as<bool> () ) {
      doVersion ();
      doHelp ( argv[0] );
      exit = 1;
    } else if ( vm["version"].as<bool> () ) {
      doVersion ();
      exit = 1;
    }

    if ( vm["dump"].as<bool> () ) {
      doDump ( vm );
    }

    if ( exit == 0 ) {
      try {
        DataCollector collector;
        collector.setCommitInterval ( vm["storage.commit"].as<unsigned> () );
        if ( vm.count ( "input" ) ) {
          SQLParserContext context ( &collector );
          setupDriver ( context, vm );
          std::string file = vm["input"].as<std::string> ();
          if ( file == "-" ) {
            context.parseStdIn ();
          } else {
            context.parseFile ( file );
          }
        } else {
          if ( !vm.count ( "monitor.host" ) ) {
            throw std::runtime_error ( "monitor.host is required" );
          }
          if ( !vm.count ( "monitor.user" ) ) {
            throw std::runtime_error ( "monitor.user is required" );
          }
          if ( !vm.count ( "storage.url" ) ) {
            throw std::runtime_error ( "storage.url is required" );
          }
          LogFileFetcher fetcher;
          DataStore dataStore;
          fetcher.setConnection ( vm["monitor.host"].as<std::string> (), vm["monitor.user"].as<std::string> (),
                                  vm["monitor.password"].as<std::string> () );
          dataStore.setConnection ( vm["storage.url"].as<std::string> () );
          collector.setMonitoredHost ( vm["monitor.host"].as<std::string> () );
          collector.setDataStore ( &dataStore );
          if ( fetcher.fetchLogs ( collector.getHost () ) ) {
            while ( exit == 0 && fetcher.hasMoreLogs () ) {
              collector.setCurrentFileSize ( fetcher.currentLogFileSize () );
              FILE *handle = fetcher.fileHandle ();
              SQLParserContext context ( &collector );
              context.setFileName ( fetcher.currentLogFile () );
              setupDriver ( context, vm );
              context.parseFileHandle ( handle, fetcher.currentLogFile () );
              int rt = pclose ( handle );
              if ( rt != 0 ) {
                std::cerr << "mysqlbinlog exited with " << rt << std::endl;
                exit = 1;
              } else {
                fetcher.next ();
              }
            }
          }
        }
        if ( vm["print"].as<bool> () ) {
          collector.dump ();
        }
      } catch ( std::exception &e ) {
        std::cerr << e.what () << std::endl;
        exit = 1;
      }
    }
  } catch ( po::error &e ) {
    std::cerr << e.what () << std::endl;
  } catch ( std::exception &e ) {
    std::cerr << "Unhandled exception " << typeid ( e ).name () << ": " << e.what () << std::endl;
  }

  return exit;
}

void APPMain::setupDriver ( SQLParserContext &driver, const boost::program_options::variables_map &vm ) const {
  if ( vm["debug"].as<int> () ) {
    driver.setDebugStream ( &std::cout );
  }
  driver.setDebug ( vm["debug"].as<int> () );
  driver.setVerbose ( vm["verbose"].as<int> () );
  if (vm.count ("monitor.ignoredb")) {
    std::vector<std::string> ignoredb = vm["monitor.ignoredb"].as<std::vector<std::string> > ();
    for ( std::vector<std::string>::iterator it = ignoredb.begin (); it != ignoredb.end (); ++it ) {
      driver.addIgnoreDB ( *it );
    }
  }
}

void APPMain::parseConfig ( boost::program_options::variables_map &vm ) {
#ifdef HAVE_PARSE_CONFIG_FILE
  std::string configFile = vm["config"].as<std::string> ();
#ifdef HAVE_ABSOLUTE
  configFile = absolute ( boost::filesystem::path ( configFile ) ).generic_string ();
#endif
  if ( boost::filesystem::exists ( configFile ) || !vm["config"].defaulted () ) {
    po::store ( po::parse_config_file<char> ( configFile.c_str (), config ), vm );
  }
#endif
}

void APPMain::doHelp ( const char *basename ) {
  std::cout << "usage: " << basename << " options/config" << std::endl;
  std::cout << options << std::endl;
}

void APPMain::doVersion () {
  std::cout << NAME " " VERSION << std::endl;
}

void APPMain::doDump ( po::variables_map vm ) {
  std::vector<boost::shared_ptr<boost::program_options::option_description> > configOptions = config.options ();
  for ( std::vector<boost::shared_ptr<po::option_description> >::iterator it = configOptions.begin ();
        it != configOptions.end (); ++it ) {
    std::cout << ( *it )->key ( "*" ) << " = ";
    if ( !vm[( *it )->key ( "*" )].empty () ) {
      std::cout << vm[( *it )->key ( "*" )];
    } else {
      std::cout << "(unset)";
    }
    std::cout << std::endl;
//    std::cout << it->first << " = " << it->second << std::endl;
  }

  for ( po::variables_map::iterator it = vm.begin (); it != vm.end (); ++it ) {
    if ( config.find_nothrow ( it->first, false ) ) {

    }
  }
}
