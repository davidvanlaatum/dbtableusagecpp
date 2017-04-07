//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLOBJECT_H
#define DBTABLEUSAGECPP_SQLOBJECT_H

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <ostream>
#include "SQLTreeWalker.h"

#ifndef EMPTY_CONSTRUCTOR
#define EMPTY_CONSTRUCTOR(type)
#endif

class SQLParserContext;

/*abstract*/ class SQLObject {
public:
    virtual ~SQLObject ();
    virtual std::string toString () const = 0;
    virtual void resolve ( SQLParserContext *context ) = 0;
    virtual void walk ( SQLTreeWalker *walker ) = 0;
    virtual SQLObject *clone () const = 0;

    friend std::ostream &operator<< ( std::ostream &os, const SQLObject &statement );
    friend std::ostream &operator<< ( std::ostream &os, const SQLObject *statement );

    static std::string toString ( const SQLObject *const object );

    template<class T> static inline std::string toString ( const boost::scoped_ptr<T> &object ) {
      return toString ( object.get () );
    }

    template<class T> static inline std::string toString ( const boost::shared_ptr<T> &object ) {
      return toString ( object.get () );
    }
};


#endif //DBTABLEUSAGECPP_SQLOBJECT_H
