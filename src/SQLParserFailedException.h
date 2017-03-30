//
// Created by David van Laatum on 29/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLPARSERFAILEDEXCEPTION_H
#define DBTABLEUSAGECPP_SQLPARSERFAILEDEXCEPTION_H

#include <stdexcept>
class SQLParserFailedException : public std::runtime_error {
public:
    SQLParserFailedException ( const std::string &msg );
    SQLParserFailedException ( const char *msg );
    SQLParserFailedException ( const std::runtime_error &e );
};

#endif //DBTABLEUSAGECPP_SQLPARSERFAILEDEXCEPTION_H
