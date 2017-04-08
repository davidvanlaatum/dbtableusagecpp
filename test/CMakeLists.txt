add_executable(runUnitTests tests.cpp SQLIdentifierTest.cpp HostTest.cpp)
target_link_libraries(runUnitTests shared GTest GMock GMockMain)
add_test(NAME unittests COMMAND runUnitTests)
set_property(TEST unittests PROPERTY ENVIRONMENT "GTEST_OUTPUT=xml:unit.xml")
if (coverage)
    include(CodeCoverage)
    setup_target_for_coverage(runUnitTests_coverage runUnitTests coverage)
    setup_target_for_coverage_cobertura(runUnitTests_cobertura runUnitTests coverage --gtest_output=xml:coverage.junit.xml)
endif ()

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SQLTests.cpp PROPERTIES GENERATED TRUE)

add_custom_command(OUTPUT SQLTests.cpp COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/buildSQLTest.sh ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS SQLTests.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/../src/SQL/*.h ${CMAKE_CURRENT_SOURCE_DIR}/buildSQLTest.sh)
add_executable(autotest ${CMAKE_CURRENT_BINARY_DIR}/SQLTests.cpp)
target_link_libraries(autotest shared GTest GMock GMockMain)
add_test(NAME autotest COMMAND autotest)
set_property(TEST autotest PROPERTY ENVIRONMENT "GTEST_OUTPUT=xml:autotest.xml")
