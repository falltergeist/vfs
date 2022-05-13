cmake_minimum_required(VERSION 3.8)
project (vfs VERSION 0.1.0 DESCRIPTION "Virtual File System")

# initializes ${CMAKE_INSTALL_*DIR} to sane defaults
include(GNUInstallDirs)

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
    message(FATAL_ERROR "zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(SYSTEM ${ZLIB_INCLUDE_DIRS})

add_library(falltergeist_vfs
    src/DatArchiveDriver.cpp
    src/DatArchiveFile.cpp
    src/DatArchiveStreamWrapper.cpp
    src/MemoryDriver.cpp
    src/MemoryFile.cpp
    src/NativeDriver.cpp
    src/NativeFile.cpp
    src/VFS.cpp
)

list(APPEND HEADER_FILES_LIST
    src/DatArchiveDriver.h
    src/DatArchiveEntry.h
    src/DatArchiveFile.h
    src/DatArchiveStreamWrapper.h
    src/IDriver.h
    src/IFile.h
    src/MemoryDriver.h
    src/MemoryFile.h
    src/NativeDriver.h
    src/NativeFile.h
    src/VFS.h
)
list(JOIN HEADER_FILES_LIST "\;" HEADER_FILES_LIST_STRING)

set_target_properties(falltergeist_vfs PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ${HEADER_FILES_LIST_STRING}
)

target_include_directories(falltergeist_vfs PRIVATE src)

target_link_libraries(
    falltergeist_vfs
    ${ZLIB_LIBRARIES}
)

install(
    TARGETS falltergeist_vfs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/falltergeist/vfs
)
