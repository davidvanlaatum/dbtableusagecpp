//
// Created by David van Laatum on 27/3/17.
//

#include "SQLDeleteStatement.h"

std::string SQLDeleteStatement::toString () const {
  return "DELETE";
}

SQLDeleteStatement::SQLDeleteStatement ( const std::string &table, SQLExpression *where ) : table ( table ),
                                                                                            where ( where ) {
}
