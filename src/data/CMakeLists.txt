add_library(data OBJECT
        DB.cpp DB.h
        Host.cpp Host.h
        Table.cpp Table.h
        DataCollector.cpp DataCollector.h
        LogFileFetcher.cpp LogFileFetcher.h DataStore.cpp DataStore.h DBObject.cpp DBObject.h)
target_include_directories(data SYSTEM PRIVATE $<TARGET_PROPERTY:Boost::boost,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(data SYSTEM PUBLIC ${SOCI_INCLUDE_DIR})
target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} $<TARGET_PROPERTY:sqlParser,INCLUDE_DIRECTORIES>)
get_target_property(E data INCLUDE_DIRECTORIES)
message("INCLUDES=${E}")
