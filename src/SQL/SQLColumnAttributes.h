//
// Created by David van Laatum on 7/4/17.
//

#ifndef DBTABLEUSAGECPP_SQLCOLUMATTRIBUTES_H
#define DBTABLEUSAGECPP_SQLCOLUMATTRIBUTES_H

#include "SQLObject.h"
namespace SQL {
  class SQLColumnAttributes : public SQLObject {
  public:
      SQLColumnAttributes ();
      virtual ~SQLColumnAttributes ();
      virtual std::string toString () const;
      virtual void resolve ( SQLParserContext *context );
      virtual void walk ( SQLTreeWalker *walker );
      virtual SQLColumnAttributes *clone () const;
      virtual void notNull ();
      virtual void null ();
      virtual void addDefault ( char *value );
      virtual void addDefault ( int value );
      virtual void addDefault ( double value );
      virtual void addDefault ( bool value );
      virtual void autoIncrement ();
      virtual void addComment ( char *value );
  private:
      bool isNull;
      std::string defaultString;
      int defaultInt;
      double defaultDouble;
      bool defaultBool;
      bool isAutoIncrement;
      std::string comment;
  };
}

#endif //DBTABLEUSAGECPP_SQLCOLUMATTRIBUTES_H
