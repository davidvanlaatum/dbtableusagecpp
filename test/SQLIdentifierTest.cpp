//
// Created by David van Laatum on 1/4/17.
//

#include <gtest/gtest.h>
#include "SQLIdentifier.h"

using namespace testing;

TEST( SQLIdentifierTest, Test1 ) {
  SQLIdentifier id ( "`id`" );
  EXPECT_EQ ( id.toString (), "`id`" );
  EXPECT_EQ ( (std::string) id, "id" );
  EXPECT_EQ ( id.getId (), "id" );

  id = SQLIdentifier ( "\"id2\"" );
  EXPECT_EQ ( id.toString (), "`id2`" );
  EXPECT_EQ ( (std::string) id, "id2" );
  EXPECT_EQ ( id.getId (), "id2" );
}
