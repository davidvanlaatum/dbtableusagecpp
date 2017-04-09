//
// Created by David van Laatum on 9/4/17.
//

#ifndef DBTABLEUSAGECPP_MYSQLPREPOPULATER_H
#define DBTABLEUSAGECPP_MYSQLPREPOPULATER_H

#include <string>
class Host;

class MySQLPrePopulater {
public:
    MySQLPrePopulater ( std::string host, std::string user, std::string pass );
    void populate ( Host *pHost );
private:
    std::string host;
    std::string user;
    std::string pass;
};


#endif //DBTABLEUSAGECPP_MYSQLPREPOPULATER_H
