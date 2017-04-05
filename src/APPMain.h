//
// Created by David van Laatum on 31/3/17.
//

#ifndef DBTABLEUSAGECPP_APPMAIN_H
#define DBTABLEUSAGECPP_APPMAIN_H
#include <boost/program_options.hpp>

namespace po = boost::program_options;

class APPMain {
public:
    APPMain ();
    int main ( int argc, const char *argv[] );
    void parseConfig ( boost::program_options::variables_map &vm );
    void doVersion ();
    void doHelp ( const char *basename );
    void doDump ( po::variables_map vm );
private:
    po::options_description options;
    po::options_description config;
};


#endif //DBTABLEUSAGECPP_APPMAIN_H
