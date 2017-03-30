#include <iostream>
#include <sstream>
#include "SQLParserContext.h"
#include "SQLParserDriver.h"
#include "sql-parser.hpp"

using namespace std;
using namespace yy;

int main ( int argc, char *argv[] ) {
  try {
    SQLParserDriver driver;
    if ( argc > 1 ) {
      driver.parseFile ( argv[1], NULL );
    } else {
      driver.parseStdIn ( NULL );
    }
  } catch ( std::exception &e ) {
    yy::SQLParser::syntax_error *e2;
    if ( ( e2 = dynamic_cast<yy::SQLParser::syntax_error *> (&e) ) != NULL ) {
      std::cerr << e2->location << ": ";
    }
    std::cerr << e.what () << std::endl;
    exit ( 1 );
  } catch ( ... ) {
    std::cerr << "unexpected exception" << std::endl;
  }

  return 0;
}
