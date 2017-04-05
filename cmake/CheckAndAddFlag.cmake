function(CheckAndAddFlag flag addto)
    set(NAME "accepts_flag_${flag}")
    string(REPLACE "-" "" NAME ${NAME})
    string(REPLACE "+" "p" NAME ${NAME})
    string(REPLACE "=" "_" NAME ${NAME})
    if (${NAME} STREQUAL "accepts_flag_coverage")
        SET(OLD_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    endif ()
    CHECK_CXX_COMPILER_FLAG("${flag}" "${NAME}")
    if (OLD_CMAKE_CXX_FLAGS)
        SET(CMAKE_CXX_FLAGS "${OLD_CMAKE_CXX_FLAGS}")
        unset(OLD_CMAKE_CXX_FLAGS)
    endif ()
    if (${NAME})
        SET(${addto} "${${addto}} ${flag}" PARENT_SCOPE)
    endif ()
endfunction()