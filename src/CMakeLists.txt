cmake_minimum_required (VERSION 2.8)

project (RASPOZNAVAYKA)

include_directories (
    ./
)

#set (AQUILA_LIB
#    aquila-src
#)

add_subdirectory (aquila-src ../build/lib)

set (HEADERS
    raspoznavayka.h
    CInputAudio.h
)
set (SOURCES
    raspoznavayka.cpp
    CInputAudio.cpp
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries (${PROJECT} aquila-src)
