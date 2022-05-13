cmake_minimum_required(VERSION 3.8)
project(falltergeist_vfs VERSION 0.1.0 DESCRIPTION "Virtual File System")

# initializes ${CMAKE_INSTALL_*DIR} to sane defaults
include(GNUInstallDirs)

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
    PUBLIC_HEADER include/falltergeist/vfs.h
)

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

# without it public headers won't get installed
set(PUBLIC_HEADERS
    src/DatArchiveDriver.h
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
install(FILES ${PUBLIC_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/falltergeist/vfs)

target_link_libraries(
    ${PROJECT_NAME}
    ${ZLIB_LIBRARIES}
)

# install the target and create export-set
install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    # these get default values from GNUInstallDirs, no need to set them
    #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    # except for public headers, as we want them to be inside a library folder
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
