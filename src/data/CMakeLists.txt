add_library(data OBJECT
        DB.cpp DB.h
        Host.cpp Host.h
        Table.cpp Table.h
        DataCollector.cpp DataCollector.h
        DataStore.cpp DataStore.h DBObject.cpp DBObject.h)
target_include_directories(data SYSTEM PRIVATE $<TARGET_PROPERTY:Boost::boost,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(data SYSTEM PUBLIC ${SOCI_INCLUDE_DIR})
target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} $<TARGET_PROPERTY:sqlParser,INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:util,INCLUDE_DIRECTORIES>)
add_dependencies(data sqlParser)
