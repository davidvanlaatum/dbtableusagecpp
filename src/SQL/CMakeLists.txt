add_definitions(-DYYDEBUG) # -DYY_NO_INPUT -DYY_NO_UNPUT)
bison_target(SQLPARSER sql-parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/sql-parser.cpp) # COMPILE_FLAGS "-v --feature=caret -r all")
flex_target(SQLSCANNER sql-lexer.l ${CMAKE_CURRENT_BINARY_DIR}/sql-lexer.cpp) # COMPILE_FLAGS --noline)
ADD_FLEX_BISON_DEPENDENCY(SQLSCANNER SQLPARSER)

add_library(sqlParser OBJECT
        sql-parser.ypp sql-lexer.l
        ${BISON_SQLPARSER_OUTPUTS} ${FLEX_SQLSCANNER_OUTPUTS}
        SQLParserContext.cpp SQLParserContext.h
        SQLStatement.cpp SQLStatement.h
        SQLBinLogStatement.cpp SQLBinLogStatement.h
        SQLObject.cpp SQLObject.h
        SQLObjectList.h
        SQLSetStatement.cpp SQLSetStatement.h
        SQLSetPair.cpp SQLSetPair.h
        SQLString.cpp SQLString.h
        SQLDefault.cpp SQLDefault.h
        SQLInteger.cpp SQLInteger.h
        SQLDeleteStatement.cpp SQLDeleteStatement.h
        SQLExpression.cpp SQLExpression.h
        SQLParserCallback.h
        SQLParserFailedException.cpp SQLParserFailedException.h
        SQLUseDatabase.cpp SQLUseDatabase.h
        SQLIdentifier.cpp SQLIdentifier.h
        SQLTable.cpp SQLTable.h
        SQLFunction.cpp SQLFunction.h
        SQLReplaceIntoStatement.cpp SQLReplaceIntoStatement.h
        SQLColumn.cpp SQLColumn.h
        SQLAnd.cpp SQLAnd.h
        SQLOr.cpp SQLOr.h
        SQLComparision.cpp SQLComparision.h
        SQLEquals.cpp SQLEquals.h
        SQLTreeWalker.h
        SQLCreateDatabaseStatement.cpp SQLCreateDatabaseStatement.h
        MySQLEvents.h
        MySQLEventParser.cpp MySQLEventParser.h
        MySQLTableMapEntry.cpp MySQLTableMapEntry.h
        MySQLBinLogWriteRowsEvent.cpp MySQLBinLogWriteRowsEvent.h
        MySQLBinLogEvent.cpp MySQLBinLogEvent.h
        MySQLBinLogUpdateRowsEvent.cpp MySQLBinLogUpdateRowsEvent.h
        MySQLBinLogDeleteRowsEvent.cpp MySQLBinLogDeleteRowsEvent.h
        SQLCreateTableStatement.cpp SQLCreateTableStatement.h
        SQLBeginStatement.cpp SQLBeginStatement.h
        SQLRollbackStatement.cpp SQLRollbackStatement.h
        SQLCommitStatement.cpp SQLCommitStatement.h
        SQLAlterTableStatement.cpp SQLAlterTableStatement.h
        SQLTableAddColumn.cpp SQLTableAddColumn.h
        SQLTableDropColumn.cpp SQLTableDropColumn.h
        SQLTableModifyColumn.cpp SQLTableModifyColumn.h
        SQLColumnDefinition.cpp SQLColumnDefinition.h
        SQLDataType.cpp SQLDataType.h
        SQLColumnAttributes.cpp SQLColumnAttributes.h
        SQLDecimal.cpp SQLDecimal.h)
target_include_directories(sqlParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(sqlParser SYSTEM PRIVATE ${GLib_INCLUDE_DIRS}
        $<TARGET_PROPERTY:Boost::boost,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:util,INCLUDE_DIRECTORIES>)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES position.hh location.hh stack.hh)
