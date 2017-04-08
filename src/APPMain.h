//
// Created by David van Laatum on 31/3/17.
//

#ifndef DBTABLEUSAGECPP_APPMAIN_H
#define DBTABLEUSAGECPP_APPMAIN_H
#include <boost/program_options.hpp>
#include <SQLParserContext.h>

namespace po = boost::program_options;

class APPMain {
public:
    APPMain ();
    int main ( int argc, char *argv[] );
    void parseConfig ( boost::program_options::variables_map &vm );
    void doVersion ();
    void doHelp ( const char *basename );
    void doDump ( po::variables_map vm );
private:
    po::options_description options;
    po::options_description config;
    void setupDriver ( SQL::SQLParserContext &driver, const boost::program_options::variables_map &vm ) const;
};


#endif //DBTABLEUSAGECPP_APPMAIN_H
