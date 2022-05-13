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
    include/falltergeist/vfs/DatArchiveDriver.h
    include/falltergeist/vfs/DatArchiveFile.h
    include/falltergeist/vfs/DatArchiveStreamWrapper.h
    include/falltergeist/vfs/IDriver.h
    include/falltergeist/vfs/IFile.h
    include/falltergeist/vfs/MemoryDriver.h
    include/falltergeist/vfs/MemoryFile.h
    include/falltergeist/vfs/NativeDriver.h
    include/falltergeist/vfs/NativeFile.h
    include/falltergeist/vfs/VFS.h
    include/falltergeist/vfs.h
)
foreach(header ${PUBLIC_HEADERS})
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${header}")
    get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
    install(
        FILES ${header}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
    )
endforeach()

target_link_libraries(
    ${PROJECT_NAME}
    ${ZLIB_LIBRARIES}
)

#install(
#    TARGETS ${PROJECT_NAME}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/falltergeist/vfs
#)
