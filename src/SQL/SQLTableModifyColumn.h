//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLALTERTABLEMODIFYCOLUMN_H
#define DBTABLEUSAGECPP_SQLALTERTABLEMODIFYCOLUMN_H
#include "SQLAlterTableStatement.h"
namespace SQL {
  class SQLColumnDefinition;
  class SQLTableModifyColumn : public SQLAlterTableColumnOperation {
  public:
      EMPTY_CONSTRUCTOR( SQLTableModifyColumn )
      SQLTableModifyColumn ( SQLColumnDefinition *p );
      virtual ~SQLTableModifyColumn ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLTableModifyColumn *clone () const;
  private:
      boost::shared_ptr<SQLColumnDefinition> definition;
  };
}


#endif //DBTABLEUSAGECPP_SQLALTERTABLEMODIFYCOLUMN_H
