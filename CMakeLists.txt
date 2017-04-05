list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0048 NEW)
project(dbtableusagecpp VERSION 1.0.0.0)

option(test "Build all tests." OFF)
option(coverage "Build coverage tests." OFF)

set(CMAKE_CXX_STANDARD 98)
include(CheckCXXCompilerFlag)
include(CheckAndAddFlag)
include(CheckCXXSymbolExists)

CheckAndAddFlag(-Wall CMAKE_CXX_FLAGS)
CheckAndAddFlag(-Wpedantic CMAKE_CXX_FLAGS)
CheckAndAddFlag(-Wno-variadic-macros CMAKE_CXX_FLAGS)
CheckAndAddFlag(-Wno-long-long CMAKE_CXX_FLAGS)
CheckAndAddFlag(-Wno-c99-extensions CMAKE_CXX_FLAGS)
CheckAndAddFlag(-O0 CMAKE_CXX_FLAGS_DEBUG)
CheckAndAddFlag(-g CMAKE_CXX_FLAGS_DEBUG)

if (test AND coverage)
    CheckAndAddFlag(--coverage CMAKE_CXX_FLAGS_DEBUG)
    CheckAndAddFlag(-fprofile-arcs CMAKE_CXX_FLAGS_DEBUG)
    CheckAndAddFlag(-ftest-coverage CMAKE_CXX_FLAGS_DEBUG)
endif ()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(Soci REQUIRED)
find_package(GLib REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options filesystem date_time)
find_package(Git)
if(GIT_FOUND)
    execute_process(COMMAND git rev-parse HEAD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

set(CMAKE_REQUIRED_LIBRARIES Boost::filesystem)
CHECK_CXX_SYMBOL_EXISTS(boost::filesystem::absolute boost/filesystem.hpp FILESYSTEM_ABSOLUTE)
if(FILESYSTEM_ABSOLUTE)
    add_definitions(-DHAVE_ABSOLUTE)
endif()
set(CMAKE_REQUIRED_LIBRARIES Boost::program_options)
CHECK_CXX_SOURCE_COMPILES("#include <boost/program_options.hpp>
    int main() {
    boost::program_options::parse_config_file<char>(NULL,NULL);
    return 0;
}" PARSE_CONFIG_FILE)
if(PARSE_CONFIG_FILE)
    add_definitions(-DHAVE_PARSE_CONFIG_FILE)
endif()
unset(CMAKE_REQUIRED_LIBRARIES)

#include_directories(${SOCI_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/src)

add_subdirectory(src)
if (test)
    enable_testing()
    include(GTest)
    add_subdirectory(test)
endif()
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage.info coverage.junit.xml coverage.xml)
include(CPack)
configure_file(src/appversion.h.in src/appversion.h)
