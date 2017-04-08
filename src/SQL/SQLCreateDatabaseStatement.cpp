#include "SQLCreateDatabaseStatement.h"

SQL::SQLCreateDatabaseStatement::SQLCreateDatabaseStatement ( SQLIdentifier *name ) : name ( name ) {
}

SQL::SQLCreateDatabaseStatement::~SQLCreateDatabaseStatement () {
  name.reset ();
}

void SQL::SQLCreateDatabaseStatement::getTables ( SQLStatement::table_type &rt ) const {

}

std::string SQL::SQLCreateDatabaseStatement::toString () const {
  return "CREATE DATABASE " + SQLObject::toString ( name );
}

void SQL::SQLCreateDatabaseStatement::resolve ( SQLParserContext *context ) {
// TODO
}

void SQL::SQLCreateDatabaseStatement::walk ( SQLTreeWalker *walker ) {
// TODO
}

SQL::SQLCreateDatabaseStatement *SQL::SQLCreateDatabaseStatement::clone () const {
  SQLCreateDatabaseStatement *rt = new SQLCreateDatabaseStatement ( NULL );
  rt->name = name;
  return rt;
}

size_t SQL::SQLCreateDatabaseStatement::showAtVerboseLevel () const {
  return 1;
}
