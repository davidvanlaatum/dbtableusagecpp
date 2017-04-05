//
// Created by David van Laatum on 28/3/17.
//

#ifndef DBTABLEUSAGECPP_HOST_H
#define DBTABLEUSAGECPP_HOST_H

#include <string>
#include <map>
#include <list>
#include <boost/scoped_ptr.hpp>
#include "DB.h"

class Host {
public:
    DB *getDB ( std::string name );
    void getDBs (std::list<DB *> &rt);

private:
    std::map<std::string, DB> dbs;
};


#endif //DBTABLEUSAGECPP_HOST_H
