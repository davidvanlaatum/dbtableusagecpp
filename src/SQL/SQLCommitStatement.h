//
// Created by David van Laatum on 5/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCOMMITSTATEMENT_H
#define DBTABLEUSAGECPP_SQLCOMMITSTATEMENT_H

#include "SQLStatement.h"
namespace SQL {
  class SQLCommitStatement : public SQLStatement {
  public:
      EMPTY_CONSTRUCTOR( SQLCommitStatement )
      virtual ~SQLCommitStatement ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLCommitStatement *clone () const;
      virtual void getTables ( table_type &rt ) const;
      virtual size_t showAtVerboseLevel () const;
  };
}

#endif //DBTABLEUSAGECPP_SQLCOMMITSTATEMENT_H
