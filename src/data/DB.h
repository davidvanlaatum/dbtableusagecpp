//
// Created by David van Laatum on 28/3/17.
//

#ifndef DBTABLEUSAGECPP_DB_H
#define DBTABLEUSAGECPP_DB_H


#include <string>
#include <map>
#include <list>
#include "Table.h"
class DB {
public:
    Table *getTable ( std::string name );
    DB *setName ( std::string name );
    const std::string &getName () const;
    void getTables ( std::list<Table *> &rt );

private:
    std::string name;
    std::map<std::string, Table> tables;
};


#endif //DBTABLEUSAGECPP_DB_H
