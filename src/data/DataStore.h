//
// Created by David van Laatum on 6/4/17.
//

#ifndef DBTABLEUSAGECPP_DATASTORE_H
#define DBTABLEUSAGECPP_DATASTORE_H

#include "soci.h"
#include "Host.h"

using namespace soci;

class DataStore {
public:
    DataStore ();
    virtual ~DataStore ();
    void setConnection ( std::string url );
    bool load ( Host &host, std::string name );
    void save ( Host &host );
    void save ( DB &db, int host );
    void save ( Table &table, int db );
    size_t getSaveCount () const;

private:
    size_t saveCount;
    std::string url;
    session sql;
};


#endif //DBTABLEUSAGECPP_DATASTORE_H
