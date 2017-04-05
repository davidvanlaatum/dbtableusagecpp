//
// Created by David van Laatum on 26/3/17.
//

#include "SQLSetStatement.h"

SQLSetStatement::SQLSetStatement ( SQLObjectList<> *args ) {
  if ( args ) {
    for ( SQLObjectList<>::iterator it = args->begin (); it != args->end (); ++it ) {
      if ( SQLSetPair *setPair = dynamic_cast<class SQLSetPair *>(*it) ) {
        this->args.push ( setPair->clone () );
      }
    }
  }
}

SQLSetStatement::~SQLSetStatement () {
  for(ArgsType::iterator it = args.begin (); it != args.end (); ++it) {
    delete *it;
  }
  args.clear ();
}

std::string SQLSetStatement::toString () const {
  return std::string ( "Set " ) + args.toString ();
}

const SQLSetStatement::ArgsType &SQLSetStatement::getArgs () const {
  return args;
}

SQLSetStatement::SQLSetStatement () {

}

void SQLSetStatement::getTables ( table_type &rt ) const {

}

void SQLSetStatement::resolve ( SQLParserContext *context ) {
  for ( ArgsType::iterator it = args.begin (); it != args.end (); ++it ) {
    ( *it )->resolve ( context );
  }
}

void SQLSetStatement::walk ( SQLTreeWalker *walker ) {
  for ( ArgsType::iterator it = args.begin (); it != args.end (); ++it ) {
    walker->walk ( *it );
  }
}

SQLSetStatement *SQLSetStatement::clone () const {
  return new SQLSetStatement ( (SQLObjectList<> *) &args );
}
