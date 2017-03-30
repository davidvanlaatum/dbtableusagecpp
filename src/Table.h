//
// Created by David van Laatum on 28/3/17.
//

#ifndef DBTABLEUSAGECPP_TABLE_H
#define DBTABLEUSAGECPP_TABLE_H


#include <string>
class Table {
public:
    Table *setName ( std::string name );
    const std::string &getName () const;

private:
    std::string name;
};


#endif //DBTABLEUSAGECPP_TABLE_H
