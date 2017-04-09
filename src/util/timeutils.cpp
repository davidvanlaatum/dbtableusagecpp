//
// Created by David van Laatum on 9/4/17.
//

#include <string>
#include <sstream>
#include <boost/date_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include "timeutils.h"

using namespace boost::posix_time;
using namespace boost::local_time;
typedef boost::date_time::c_local_adjustor<ptime> local_adj;

std::string toString ( time_t t ) {
  std::stringstream s;

  if ( t != 0 ) {
    const ptime &ptime = from_time_t ( t );
    s << local_adj::utc_to_local ( ptime );
  } else {
    s << "never";
  }
  return s.str ();
}
