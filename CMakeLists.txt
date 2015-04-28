cmake_minimum_required(VERSION 2.8)

project(TextMining)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-O0 -std=c++11")

include(FindPkgConfig)
pkg_check_modules (LIBUSB REQUIRED libusb-1.0)
include_directories (${LIBUSB_INCLUDE_DIRS})
link_directories (${LIBUSB_LIBRARY_DIRS})

include_directories("include/")

file(GLOB_RECURSE SRC_FILES src/*)
file(GLOB_RECURSE INCLUDE_FILES include/*)
add_library(TextMining SHARED ${SRC_FILES} ${INCLUDE_FILES})
include_directories(${PROJECT_SOURCE_DIR}/bin)

add_executable(TextMiningCompiler bin/TextMiningCompiler.cpp)
target_link_libraries(TextMiningCompiler TextMining)

add_executable(TextMiningApp bin/TextMiningApp.cpp)
target_link_libraries(TextMiningApp TextMining)
