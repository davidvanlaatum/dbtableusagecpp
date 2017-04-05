add_library(data
        DB.cpp DB.h
        Host.cpp Host.h
        Table.cpp Table.h
        DataCollector.cpp DataCollector.h
        )
target_link_libraries(data sqlParser)
target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${SOCI_INCLUDE_DIR})
