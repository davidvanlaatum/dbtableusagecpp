//
// Created by David van Laatum on 29/3/17.
//

#define GMOCK
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SQLParserDriver.h>

using namespace testing;

TEST( ScanBuffer, Buffer ) {
  SQLParserDriver driver;
  StrictMock<MockSQLParserCallback> callback;
  EXPECT_CALL ( callback, statement ( _, _ ) );
  driver.parseString ( "SET TIMESTAMP=123;", &callback );
}

TEST ( ErrorTests, UnclosedComment ) {
  SQLParserDriver driver;
  ASSERT_THROW( driver.parseString ( "/*", NULL ), std::runtime_error );
}
