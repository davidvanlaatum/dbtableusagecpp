//
// Created by David van Laatum on 6/4/17.
//

#include "DBObject.h"

DBObject::DBObject () {
  changedValue = false;
}

void DBObject::changed () {
  changedValue = true;
}

bool DBObject::hasChanged () {
  return changedValue;
}

void DBObject::clearChanged () {
  changedValue = false;
}
