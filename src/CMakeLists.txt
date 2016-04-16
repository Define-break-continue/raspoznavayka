cmake_minimum_required (VERSION 2.8)

set(PROJECT raspoznavayka)

project (${PROJECT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#include_directories (
#    ./
#)

add_library(aquila STATIC IMPORTED)
add_library(ooura STATIC IMPORTED)

set_property(TARGET aquila PROPERTY
             IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/aquila/libAquila.a)
set_property(TARGET ooura PROPERTY
             IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/aquila/libOoura_fft.a)

set_property(TARGET aquila PROPERTY CXX_STANDARD 11)
set_property(TARGET ooura PROPERTY CXX_STANDARD 11)

set (HEADERS
    raspoznavayka.h
    CInputAudio.h
    CMelody.h
)
set (SOURCES
    raspoznavayka.cpp
    CInputAudio.cpp
    CMelody.cpp
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries (${PROJECT} aquila ooura)
