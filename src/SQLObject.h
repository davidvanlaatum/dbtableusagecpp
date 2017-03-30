//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLOBJECT_H
#define DBTABLEUSAGECPP_SQLOBJECT_H


#include <ostream>
class SQLObject {
public:
    virtual ~SQLObject ();
    virtual std::string toString () const = 0;

    friend std::ostream &operator<< ( std::ostream &os, const SQLObject &statement );
    friend std::ostream &operator<< ( std::ostream &os, const SQLObject *statement );
};


#endif //DBTABLEUSAGECPP_SQLOBJECT_H
