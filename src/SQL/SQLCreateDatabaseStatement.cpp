#include "SQLCreateDatabaseStatement.h"

SQLCreateDatabaseStatement::SQLCreateDatabaseStatement ( SQLIdentifier *name ) : name ( name ) {
}

SQLCreateDatabaseStatement::~SQLCreateDatabaseStatement () {
  name.reset ();
}

void SQLCreateDatabaseStatement::getTables ( SQLStatement::table_type &rt ) const {

}

std::string SQLCreateDatabaseStatement::toString () const {
  return "CREATE DATABASE " + SQLObject::toString ( name );
}

void SQLCreateDatabaseStatement::resolve ( SQLParserContext *context ) {
// TODO
}

void SQLCreateDatabaseStatement::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQLCreateDatabaseStatement *SQLCreateDatabaseStatement::clone () const {
  SQLCreateDatabaseStatement *rt = new SQLCreateDatabaseStatement ( NULL );
  rt->name = name;
  return rt;
}
