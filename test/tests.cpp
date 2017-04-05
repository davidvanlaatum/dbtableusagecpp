//
// Created by David van Laatum on 29/3/17.
//

#define GMOCK
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SQLParserDriver.h>
#include <SQLSetStatement.h>
#include <SQLInteger.h>
#include <SQLReplaceIntoStatement.h>

using namespace testing;

MATCHER_P2 ( HasVariableWithIntValue, name, value, "" ) {
  SQLInteger *valueptr = dynamic_cast<SQLInteger *> ( arg->getValue ());
  return arg->getName () == name && valueptr != NULL && valueptr->toInt () == value;
}

TEST( ScanBuffer, Buffer ) {
  std::stringstream output;
  SQLParserDriver driver ( &output, &output, NULL );
  StrictMock<MockSQLParserCallback> callback;

  EXPECT_CALL ( callback, statement ( _, WhenDynamicCastTo<SQLSetStatement *> (
    Property ( &SQLSetStatement::getArgs, Contains (
      HasVariableWithIntValue ( "TIMESTAMP", 123 )
    ) )
  ), _ ) );
  driver.parseString ( "SET TIMESTAMP=123;", &callback );
  ASSERT_THAT ( output.str (), ContainsRegex ( "TIMESTAMP=123" ) );
}

TEST ( ErrorTests, UnclosedComment ) {
  std::stringstream output;
  SQLParserDriver driver ( &output, &output, NULL );
  StrictMock<MockSQLParserCallback> callback;
  driver.parseString ( "    /*", &callback );
  ASSERT_THAT ( output.str (), ContainsRegex ( "unclosed comment" ) );
  ASSERT_THAT ( output.str (), ContainsRegex ( "syntax error, unexpected \\$end" ) );
}

TEST ( ReplaceInto, Test1 ) {
  std::stringstream output;
  SQLParserDriver driver ( &output, &output, NULL );
  StrictMock<MockSQLParserCallback> callback;
  EXPECT_CALL ( callback, statement ( _, WhenDynamicCastTo<SQLReplaceIntoStatement *> (
    Property ( &SQLReplaceIntoStatement::getTable, Property ( &SQLTable::toString, Eq ( "`replication`" ) ) )
  ), _ ) );
  driver.parseString ( "REPLACE INTO `replication` VALUES(1, NAME_CONST('a','2017-03-26 17:42:09'))", &callback );
}

TEST ( ReplaceInto, Test2 ) {
  std::stringstream output;
  SQLParserDriver driver ( &output, &output, NULL );
  StrictMock<MockSQLParserCallback> callback;
  EXPECT_CALL ( callback, statement ( _, WhenDynamicCastTo<SQLReplaceIntoStatement *> (
    Property ( &SQLReplaceIntoStatement::getTable, Property ( &SQLTable::toString, Eq ( "`replication`" ) ) )
  ), _ ) );
  driver.parseString ( "REPLACE INTO `replication` VALUES(1, NAME_CONST('a',_latin1'2017-03-26 17:42:09' COLLATE "
                         "'latin1_swedish_ci'))", &callback );
}
