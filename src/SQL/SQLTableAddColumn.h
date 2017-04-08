//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLTABLEADDCOLUMN_H
#define DBTABLEUSAGECPP_SQLTABLEADDCOLUMN_H
#include "SQLAlterTableStatement.h"

namespace SQL {
  class SQLColumnDefinition;
  class SQLTableAddColumn : public SQLAlterTableColumnOperation {
  public:
      EMPTY_CONSTRUCTOR( SQLTableAddColumn )
      SQLTableAddColumn ( SQLColumnDefinition *p );
      virtual ~SQLTableAddColumn ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLTableAddColumn *clone () const;
  private:
      boost::shared_ptr<SQLColumnDefinition> definition;
  };
}


#endif //DBTABLEUSAGECPP_SQLTABLEADDCOLUMN_H
