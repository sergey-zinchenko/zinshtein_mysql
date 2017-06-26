cmake_minimum_required(VERSION 3.6)

project(zinshtein)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

set (MYSQL_FIND_REQUIRED on)

FIND_PACKAGE(MYSQL)

include_directories(
        ${MYSQL_INCLUDE_DIR}
)

ADD_DEFINITIONS("-DHAVE_DLOPEN")

set(CMAKE_CXX_FLAGS -Ofast)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp algo.cpp algo.h ertranslit.cpp ertranslit.h)

add_library(zinshtein SHARED ${SOURCE_FILES})