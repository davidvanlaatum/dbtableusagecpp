//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SETPAIR_H
#define DBTABLEUSAGECPP_SETPAIR_H

#include "SQLObject.h"
namespace SQL {
  class SQLSetPair : public SQLObject {
  public:
      EMPTY_CONSTRUCTOR( SQLSetPair )
      virtual ~SQLSetPair ();
      SQLSetPair ( const std::string &name, SQLObject *value );
      virtual std::string toString () const;
      const std::string &getName () const;
      SQLObject *getValue ();
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLSetPair *clone () const;
  private:
      std::string name;
      boost::shared_ptr<SQLObject> value;
  };
}


#endif //DBTABLEUSAGECPP_SETPAIR_H
