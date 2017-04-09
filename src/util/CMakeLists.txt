add_library(util OBJECT
        TeeStream.h
        byteutils.h byteutils.cpp timeutils.h timeutils.cpp)
target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(util SYSTEM PRIVATE $<TARGET_PROPERTY:Boost::boost,INTERFACE_INCLUDE_DIRECTORIES>)
