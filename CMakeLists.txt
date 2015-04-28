cmake_minimum_required(VERSION 2.8)

project(SegmentationVoices)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-O0")


include(FindPkgConfig)
pkg_check_modules (LIBUSB REQUIRED libusb-1.0)
include_directories (${LIBUSB_INCLUDE_DIRS})
link_directories (${LIBUSB_LIBRARY_DIRS})

include_directories(${NIST_INCLUDE})
link_directories(${NIST_LIB})


add_executable(seg main.cpp)

target_link_libraries(seg ${SSE_FLAGS})
