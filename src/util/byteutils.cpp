//
// Created by David van Laatum on 9/4/17.
//

#include <string>
#include <sstream>
#include <iomanip>
#include "byteutils.h"

std::string bytesToString ( double value ) {
  std::stringstream s;
  static const char *postfixes[] = { "kb", "mb", "gb", "tb" };
  size_t i = 0;
  const char *postfix = "b";

  while ( value > 1024 && i < ( sizeof ( postfixes ) / sizeof ( postfixes[0] ) ) ) {
    postfix = postfixes[i];
    value /= 1024;
    i++;
  }

  s << std::setprecision ( 3 ) << value << postfix;

  return s.str ();
}
