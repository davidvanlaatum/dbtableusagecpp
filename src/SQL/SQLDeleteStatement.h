//
// Created by David van Laatum on 27/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLDELETESTATEMENT_H
#define DBTABLEUSAGECPP_SQLDELETESTATEMENT_H

#include "SQLStatement.h"
#include "SQLExpression.h"
#include "SQLTable.h"
namespace SQL {
  class SQLDeleteStatement : public SQLStatement {
  public:
      EMPTY_CONSTRUCTOR( SQLDeleteStatement )
      SQLDeleteStatement ( SQLTable *table, SQLObject *where );
      virtual std::string toString () const;
      virtual void getTables ( table_type &rt ) const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLDeleteStatement *clone () const;
      virtual size_t showAtVerboseLevel () const;
  private:
      boost::shared_ptr<SQLTable> table;
      boost::shared_ptr<SQLObject> where;
  };
}

#endif //DBTABLEUSAGECPP_SQLDELETESTATEMENT_H
