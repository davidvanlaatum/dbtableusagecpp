//
// Created by David van Laatum on 26/3/17.
//

#include "SetStatement.h"

SetStatement::SetStatement ( SQLObjectList<> *args ) {
  for ( auto it = args->begin (); it != args->end (); ++it ) {
    if ( SetPair *SetPair = dynamic_cast<class SetPair *>(*it) ) {
      this->args.push ( SetPair );
      args->erase ( it );
    }
  }
}

SetStatement::~SetStatement () {
  for ( auto it = args.begin (); it != args.end (); ++it ) {
    delete *it;
  }
  args.clear ();
}

std::string SetStatement::toString () const {
  return std::string ( "Set " ) + args.toString ();
}

const SQLObjectList<SetPair *> &SetStatement::getArgs () const {
  return args;
}

SetStatement::SetStatement () {

}
