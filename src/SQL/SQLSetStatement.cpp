//
// Created by David van Laatum on 26/3/17.
//

#include "SQLSetStatement.h"

SQL::SQLSetStatement::SQLSetStatement ( SQL::SQLObjectList<> *args ) {
  if ( args ) {
    for ( SQLObjectList<>::iterator it = args->begin (); it != args->end (); ++it ) {
      if ( SQLSetPair *setPair = dynamic_cast<class SQLSetPair *>(*it) ) {
        this->args.push ( setPair->clone () );
      }
    }
  }
}

SQL::SQLSetStatement::~SQLSetStatement () {
  for ( ArgsType::iterator it = args.begin (); it != args.end (); ++it ) {
    delete *it;
  }
  args.clear ();
}

std::string SQL::SQLSetStatement::toString () const {
  return std::string ( "Set " ) + args.toString ();
}

const SQL::SQLSetStatement::ArgsType &SQL::SQLSetStatement::getArgs () const {
  return args;
}

SQL::SQLSetStatement::SQLSetStatement () {

}

void SQL::SQLSetStatement::getTables ( table_type &rt ) const {

}

void SQL::SQLSetStatement::resolve ( SQLParserContext *context ) {
  for ( ArgsType::iterator it = args.begin (); it != args.end (); ++it ) {
    ( *it )->resolve ( context );
  }
}

void SQL::SQLSetStatement::walk ( SQLTreeWalker *walker ) {
  for ( ArgsType::iterator it = args.begin (); it != args.end (); ++it ) {
    walker->walk ( *it );
  }
}

SQL::SQLSetStatement *SQL::SQLSetStatement::clone () const {
  return new SQLSetStatement ( (SQLObjectList<> *) &args );
}

size_t SQL::SQLSetStatement::showAtVerboseLevel () const {
  return 2;
}
