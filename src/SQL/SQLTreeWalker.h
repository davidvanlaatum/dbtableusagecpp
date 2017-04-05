//
// Created by David van Laatum on 3/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLTREEWALKER_H
#define DBTABLEUSAGECPP_SQLTREEWALKER_H

class SQLObject;

class SQLTreeWalker {
public:
    virtual void walk ( SQLObject *object ) = 0;
};


#endif //DBTABLEUSAGECPP_SQLTREEWALKER_H
