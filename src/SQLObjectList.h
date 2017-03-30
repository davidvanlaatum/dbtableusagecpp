//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLOBJECTLIST_H
#define DBTABLEUSAGECPP_SQLOBJECTLIST_H

#include <iostream>
#include <sstream>
#include <list>
#include "SQLObject.h"

template <class T=SQLObject *> class SQLObjectList : public std::list<T>, public SQLObject {
public:
    virtual std::string toString () const override {
      std::stringstream rt;
      rt << "(";

      for ( auto it = this->begin (); it != this->end (); ++it )
        rt << (it != this->begin () ? "," : "") << (*it);

      rt << ")";

      return rt.str ();
    }
    virtual void push(T object) {
      this->push_back (object);
    }
};

#endif //DBTABLEUSAGECPP_SQLOBJECTLIST_H
