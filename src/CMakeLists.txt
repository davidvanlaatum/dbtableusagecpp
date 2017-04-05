add_subdirectory(SQL)
add_subdirectory(data)
add_library(shared
        APPMain.cpp APPMain.h
)
target_link_libraries(shared ${SOCI_LIBRARY} sqlParser data Boost::boost Boost::program_options Boost::filesystem)
target_include_directories(shared PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(dbtableusagecpp main.cpp)
set_target_properties(dbtableusagecpp PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(dbtableusagecpp shared)
install(TARGETS dbtableusagecpp EXPORT dbtableusagecpp RUNTIME DESTINATION bin)
install(EXPORT dbtableusagecpp DESTINATION lib/dbtableusagecpp)
