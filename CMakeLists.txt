cmake_minimum_required(VERSION 3.8)
project (vfs)

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
    message(FATAL_ERROR "zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(SYSTEM ${ZLIB_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)

add_library(vfs ${SOURCE_FILES})

set_target_properties(vfs PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(
    vfs
    ${ZLIB_LIBRARIES}
)