//
// Created by David van Laatum on 6/4/17.
//

#ifndef DBTABLEUSAGECPP_DBOBJECT_H
#define DBTABLEUSAGECPP_DBOBJECT_H


class DBObject {
public:
    DBObject ();
    void changed ();
    bool hasChanged ();
    void clearChanged ();

private:
    bool changedValue;
};


#endif //DBTABLEUSAGECPP_DBOBJECT_H
