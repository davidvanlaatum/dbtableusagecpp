#include "SQLCreateDatabaseStatement.h"

SQLCreateDatabaseStatement::SQLCreateDatabaseStatement ( SQLIdentifier *name ) : name ( name ) {
}

SQLCreateDatabaseStatement::~SQLCreateDatabaseStatement () {
  name.reset ();
}

void SQLCreateDatabaseStatement::getTables ( SQLStatement::table_type &rt ) const {

}

std::string SQLCreateDatabaseStatement::toString () const {
  return std::string ();
}

void SQLCreateDatabaseStatement::resolve ( SQLParserContext *context ) {

}

void SQLCreateDatabaseStatement::walk ( SQLTreeWalker *walker ) {

}

SQLObject *SQLCreateDatabaseStatement::clone () const {
  SQLCreateDatabaseStatement *rt = new SQLCreateDatabaseStatement ( NULL );
  rt->name = name;
  return rt;
}
