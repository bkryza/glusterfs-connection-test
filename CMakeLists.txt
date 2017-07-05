cmake_minimum_required(VERSION 3.0)
project(glusterfs-example CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib)

find_package(Threads REQUIRED)

include(FindPkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(GLUSTERFSAPI glusterfs-api)
    if(NOT GLUSTERFSAPI_FOUND EQUAL 1)
        message(SEND_ERROR "pkg-config for glusterfs-api is missing.")
    else(NOT GLUSTERFSAPI_FOUND EQUAL 1)
        add_definitions(-DWITH_GLUSTERFS=1)
    endif(NOT GLUSTERFSAPI_FOUND EQUAL 1)
endif (PKG_CONFIG_FOUND)

find_package(Folly REQUIRED)
find_library(LIBEVENT_LIBRARY event)
find_library(IBERTY_LIBRARY iberty)
find_library(DOUBLE_CONVERSION_LIBRARY double-conversion)
find_package(Glog REQUIRED)

add_executable(glusterfs-example main.cc)
set_property(TARGET glusterfs-example PROPERTY CXX_STANDARD 14)

target_include_directories(glusterfs-example PUBLIC ${LIBEVENT_INCLUDE_DIR})


set(FOLLY_LIBRARIES
    ${FOLLY_LIBRARIES}
    ${LIBEVENT_LIBRARY}
    ${IBERTY_LIBRARY}
    ${DOUBLE_CONVERSION_LIBRARY}
    ${GLOG_LIBRARIES}
    -ldl
    -pthread)

set(PLATFORM_EXTRA_LIBS
    ${CMAKE_THREAD_LIBS_INIT}
    ${LTDL_LIBRARY}
    ${ZLIB_LIBRARY}
    ${DL_LIBRARY})

list(APPEND GLUSTERFS_EXAMPLE_LIBRARIES ${GLUSTERFSAPI_LIBRARIES})
list(APPEND GLUSTERFS_EXAMPLE_LIBRARIES ${PLATFORM_EXTRA_LIBS})
# list(APPEND GLUSTERFS_EXAMPLE_LIBRARIES ${LIBEVENT_LIBRARY})

# list(APPEND GLUSTERFS_EXAMPLE_LIBRARIES ${FOLLY_LIBRARIES})

list(APPEND GLUSTERFS_EXAMPLE_LIBRARIES ${PTHREAD_LIBRARIES})
target_link_libraries(glusterfs-example PUBLIC ${GLUSTERFS_EXAMPLE_LIBRARIES})
