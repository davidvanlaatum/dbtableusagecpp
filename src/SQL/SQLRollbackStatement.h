//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLROLLBACKSTATEMENT_H
#define DBTABLEUSAGECPP_SQLROLLBACKSTATEMENT_H

#include "SQLStatement.h"
namespace SQL {
  class SQLRollbackStatement : public SQLStatement {
  public:
      virtual ~SQLRollbackStatement ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLRollbackStatement *clone () const;
      virtual void getTables ( table_type &rt ) const;
      virtual size_t showAtVerboseLevel () const;
  };
}

#endif //DBTABLEUSAGECPP_SQLROLLBACKSTATEMENT_H
