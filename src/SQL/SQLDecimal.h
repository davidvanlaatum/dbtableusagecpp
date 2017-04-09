//
// Created by David van Laatum on 9/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLDECIMAL_H
#define DBTABLEUSAGECPP_SQLDECIMAL_H
#include "SQLObject.h"
namespace SQL {
  class SQLDecimal : public SQLObject {
  public:
      EMPTY_CONSTRUCTORI ( SQLDecimal, whole ( 0 ), fraction ( 0 ) )
      SQLDecimal ( std::string value );
      SQLDecimal ( long whole, long fraction );
      virtual ~SQLDecimal ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLDecimal *clone () const;
      virtual bool operator== ( const SQLObject &other ) const;
      long getWhole () const;
      long getFraction () const;
      // todo convert to double etc
  private:
      long whole;
      long fraction;
  };
}


#endif //DBTABLEUSAGECPP_SQLDECIMAL_H
