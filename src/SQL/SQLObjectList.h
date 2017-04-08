//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLOBJECTLIST_H
#define DBTABLEUSAGECPP_SQLOBJECTLIST_H

#include <iostream>
#include <sstream>
#include <list>
#include "SQLObject.h"
namespace SQL {
  template<typename T=SQLObject> class SQLObjectList : public std::list<T *>, public SQLObject {
  public:
      virtual ~SQLObjectList () {
        for ( typename SQLObjectList<T>::iterator it = this->begin (); it != this->end (); ++it )
          delete ( *it );
        this->clear ();
      }

      virtual std::string toString () const {
        std::stringstream rt;
        rt << "(";

        for ( typename SQLObjectList<T>::const_iterator it = this->begin (); it != this->end (); ++it )
          rt << ( it != this->begin () ? "," : "" ) << ( *it );

        rt << ")";

        return rt.str ();
      }

      virtual void push ( T *object ) {
        this->push_back ( object );
      }

      virtual void resolve ( SQLParserContext *context ) {
        for ( typename SQLObjectList<T>::iterator it = this->begin (); it != this->end (); ++it )
          ( *it )->resolve ( context );
      }

      virtual void walk ( SQLTreeWalker *walker ) {
        for ( typename SQLObjectList<T>::iterator it = this->begin (); it != this->end (); ++it )
          walker->walk ( *it );
      }

      virtual SQLObjectList<T> *clone () const {
        SQLObjectList<T> *rt = new SQLObjectList<T> ();
        for ( typename SQLObjectList<T>::const_iterator it = this->begin (); it != this->end (); ++it )
          rt->push ( ( *it )->clone () );
        return rt;
      }
  };
}

#endif //DBTABLEUSAGECPP_SQLOBJECTLIST_H
