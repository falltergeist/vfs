cmake_minimum_required(VERSION 3.8)
project(falltergeist_vfs VERSION 0.2.0 DESCRIPTION "Virtual File System")

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
    message(FATAL_ERROR "zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(SYSTEM ${ZLIB_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/DatArchiveDriver.cpp
        src/DatArchiveFile.cpp
        src/DatArchiveStreamWrapper.cpp
        src/MemoryDriver.cpp
        src/MemoryFile.cpp
        src/NativeDriver.cpp
        src/NativeFile.cpp
        src/VFS.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
)

include(GNUInstallDirs)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(
    ${PROJECT_NAME}
    ${ZLIB_LIBRARIES}
)
