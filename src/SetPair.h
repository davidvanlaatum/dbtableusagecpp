//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SETPAIR_H
#define DBTABLEUSAGECPP_SETPAIR_H

#include "SQLObject.h"
class SetPair : public SQLObject {
public:
    virtual ~SetPair ();
    SetPair ( const std::string &name, SQLObject *value );
    virtual std::string toString () const;
    const std::string &getName () const;
    SQLObject *getValue () const;

private:
    std::string name;
    SQLObject *value;
};


#endif //DBTABLEUSAGECPP_SETPAIR_H
