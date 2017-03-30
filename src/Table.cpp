//
// Created by David van Laatum on 28/3/17.
//

#include "Table.h"

Table *Table::setName ( std::string name ) {
  this->name = name;
  return this;
}

const std::string &Table::getName () const {
  return name;
}
