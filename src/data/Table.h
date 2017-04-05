//
// Created by David van Laatum on 28/3/17.
//

#ifndef DBTABLEUSAGECPP_TABLE_H
#define DBTABLEUSAGECPP_TABLE_H


#include <string>
class Table {
public:
    Table ();
    Table *setName ( std::string name );
    const std::string &getName () const;

    void updateWrite ( time_t i );
    void updateRead ( time_t i );
    void updateInsert ( time_t i );
    void updateUpdate ( time_t i );
    void updateDelete ( time_t i );
    void updateAlter ( time_t i );
    time_t getLastWrite () const;
    time_t getLastRead () const;
    time_t getCreated () const;
    time_t getLastInsert () const;
    time_t getLastUpdate () const;
    time_t getLastDelete () const;
    time_t getLastAlter () const;
private:
    std::string name;
    time_t lastWrite;
    time_t lastRead;
    time_t lastInsert;
    time_t lastUpdate;
    time_t lastDelete;
    time_t lastAlter;
    time_t created;
};


#endif //DBTABLEUSAGECPP_TABLE_H
