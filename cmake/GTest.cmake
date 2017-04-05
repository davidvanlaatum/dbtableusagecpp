find_package(Threads REQUIRED)
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
