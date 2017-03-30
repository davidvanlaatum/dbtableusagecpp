cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0048 NEW)
project(dbtableusagecpp VERSION 1.0.0)
include(CheckCXXCompilerFlag)

function(checkandaddflag flag addto)
    set(NAME "accepts_flag_${flag}")
    string(REPLACE "-" "" NAME ${NAME})
    string(REPLACE "+" "p" NAME ${NAME})
    string(REPLACE "=" "_" NAME ${NAME})
    CHECK_CXX_COMPILER_FLAG("${flag}" "${NAME}")
    if(${NAME})
        SET(${addto} "${${addto}} ${flag}" PARENT_SCOPE)
    endif()
endfunction()
checkandaddflag(-Wall CMAKE_CXX_FLAGS)
checkandaddflag(-ansi CMAKE_CXX_FLAGS)
checkandaddflag(-Wpedantic CMAKE_CXX_FLAGS)
checkandaddflag(-Wno-variadic-macros CMAKE_CXX_FLAGS)
checkandaddflag(-Wno-c++11-long-long CMAKE_CXX_FLAGS)

checkandaddflag(-O0 CMAKE_CXX_FLAGS_DEBUG)
checkandaddflag(-g CMAKE_CXX_FLAGS_DEBUG)

option(test "Build all tests." OFF)
option(coverage "Build coverage tests." OFF)
if(coverage)
    checkandaddflag(-fprofile-arcs CMAKE_CXX_FLAGS_DEBUG)
    checkandaddflag(-ftest-coverage CMAKE_CXX_FLAGS_DEBUG)
endif()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
add_definitions(-DYYDEBUG -DYY_NO_INPUT -DYY_NO_UNPUT)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
#find_package(Soci REQUIRED)
find_package(GLib REQUIRED)

include_directories(${SOCI_INCLUDE_DIR} ${GLib_INCLUDE_DIRS})

bison_target(SQLPARSER src/sql-parser.ypp src/sql-parser.cpp)
flex_target(SQLSCANNER src/sql-lexer.l src/sql-lexer.cpp)

set(SOURCE_FILES src/sql-parser.ypp src/sql-lexer.l
        src/SQLParserContext.cpp src/SQLParserContext.h
        src/SQLStatement.cpp src/SQLStatement.h
        src/SQLBinLogStatement.cpp src/SQLBinLogStatement.h
        src/SQLObject.cpp src/SQLObject.h
        src/SQLObjectList.h
        src/SetStatement.cpp src/SetStatement.h
        src/SetPair.cpp src/SetPair.h
        src/SQLString.cpp src/SQLString.h
        src/SQLDefault.cpp src/SQLDefault.h
        src/SQLInteger.cpp src/SQLInteger.h
        src/SQLDeleteStatement.cpp src/SQLDeleteStatement.h
        src/SQLExpression.cpp src/SQLExpression.h
        src/mysqlevents/events.h
        src/mysqlevents/MySQLEventParser.cpp src/mysqlevents/MySQLEventParser.h
        src/mysqlevents/MySQLTableMapEntry.cpp src/mysqlevents/MySQLTableMapEntry.h
        src/DB.cpp src/DB.h
        src/Host.cpp src/Host.h
        src/Table.cpp src/Table.h
        ${BISON_SQLPARSER_OUTPUTS} ${FLEX_SQLSCANNER_OUTPUTS}
        src/SQLParserDriver.cpp src/SQLParserDriver.h
        src/SQLParserCallback.h
        src/SQLParserFailedException.cpp src/SQLParserFailedException.h
        )

add_library(shared ${SOURCE_FILES})
target_include_directories(shared PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(shared ${MYSQL_LIBRARIES} ${SOCI_LIBRARY} ${GLib_LIBRARY})

add_executable(dbtableusagecpp src/main.cpp)
target_link_libraries(dbtableusagecpp shared)
install(TARGETS dbtableusagecpp EXPORT dbtableusagecpp RUNTIME DESTINATION bin)
install(EXPORT dbtableusagecpp DESTINATION lib/dbtableusagecpp)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES src/position.hh src/location.hh src/stack.hh
        coverage.info coverage.junit.xml coverage.xml)
if (test)
    enable_testing()
    find_package(Threads REQUIRED)
    if (coverage)
        include(CodeCoverage)
        setup_target_for_coverage(runUnitTests_coverage runUnitTests coverage)
        setup_target_for_coverage_cobertura(runUnitTests_cobertura runUnitTests coverage --gtest_output=xml:coverage.junit.xml)
    endif ()
    include(ExternalProject)
    set(GTEST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest")
    ExternalProject_Add(GTestExternal
            URL https://github.com/google/googletest/archive/release-1.8.0.zip
            URL_HASH SHA1=667f873ab7a4d246062565fad32fb6d8e203ee73
            TIMEOUT 10e
            PREFIX "${GTEST_PREFIX}"
            INSTALL_COMMAND "")

    set(LIBPREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}")
    set(LIBSUFFIX "${CMAKE_STATIC_LIBRARY_SUFFIX}")
    set(GTEST_LOCATION "${GTEST_PREFIX}/src/GTestExternal-build/googlemock/")
    set(GTEST_INCLUDES "${GTEST_PREFIX}/src/GTestExternal/googletest/include")
    set(GTEST_LIBRARY "${GTEST_LOCATION}/gtest/${LIBPREFIX}gtest${LIBSUFFIX}")

    set(GMOCK_INCLUDES "${GTEST_PREFIX}/src/GTestExternal/googlemock/include")
    set(GMOCK_LIBRARY "${GTEST_LOCATION}/${LIBPREFIX}gmock${LIBSUFFIX}")
    set(GMOCK_MAINLIB "${GTEST_LOCATION}/${LIBPREFIX}gmock_main${LIBSUFFIX}")

    add_library(GTest INTERFACE)
    set_target_properties(GTest PROPERTIES
            INTERFACE_LOCATION "${GTEST_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDES}")

    add_library(GMock INTERFACE)
    set_target_properties(GMock PROPERTIES
            INTERFACE_LOCATION "${GMOCK_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDES}")

    add_library(GMockMain IMPORTED STATIC GLOBAL)
    set_target_properties(GMockMain PROPERTIES
            IMPORTED_LOCATION "${GMOCK_MAINLIB}"
            IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")

    add_dependencies(GTest GTestExternal)
    add_dependencies(GMock GTestExternal)
    add_dependencies(GMockMain GTestExternal)
    add_executable(runUnitTests test/tests.cpp)
    target_link_libraries(runUnitTests shared GTest GMock GMockMain)
    add_test(NAME unittests COMMAND runUnitTests)
endif ()
include(CPack)
