//
// Created by David van Laatum on 29/3/17.
//

#define GMOCK
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SQLParserDriver.h>

using namespace testing;

TEST( ScanBuffer, Buffer ) {
  std::stringstream output;
  SQLParserDriver driver ( &output, &output, NULL );
  StrictMock<MockSQLParserCallback> callback;
  EXPECT_CALL ( callback, statement ( _, _ ) );
  driver.parseString ( "SET TIMESTAMP=123;", &callback );
}

TEST ( ErrorTests, UnclosedComment ) {
  std::stringstream output;
  SQLParserDriver driver ( &output, &output, NULL );
  driver.parseString ( "    /*", NULL );

  std::string first;
  std::getline (output,first);
  ASSERT_EQ(first,"buffer:1.5-6: unclosed comment");
  std::getline (output,first);
  ASSERT_EQ(first,"buffer:1.5-6: syntax error, unexpected $end at ");
}
