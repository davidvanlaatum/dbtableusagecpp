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
    std::cerr << e.what () << std::endl;
    exit ( 1 );
  } catch ( ... ) {
    std::cerr << "unexpected exception" << std::endl;
  }

  return 0;
}
