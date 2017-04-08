add_subdirectory(SQL)
add_subdirectory(data)
add_library(shared
        APPMain.cpp APPMain.h
        $<TARGET_OBJECTS:data> $<TARGET_OBJECTS:sqlParser>
        )
target_link_libraries(shared ${SOCI_LIBRARY} ${GLib_LIBRARY} Boost::boost Boost::program_options Boost::filesystem)
target_include_directories(shared PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        PUBLIC $<TARGET_PROPERTY:data,INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:sqlParser,INCLUDE_DIRECTORIES>)

add_executable(dbtableusagecpp main.cpp)
set_target_properties(dbtableusagecpp PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(dbtableusagecpp shared)
install(TARGETS dbtableusagecpp EXPORT dbtableusagecpp RUNTIME DESTINATION bin)
install(EXPORT dbtableusagecpp DESTINATION lib/dbtableusagecpp)
