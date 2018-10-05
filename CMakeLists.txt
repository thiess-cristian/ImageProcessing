cmake_minimum_required (VERSION 2.6)

project (ImageProcessing)

set(Qt5_DIR "D:/qt2/5.11.1/msvc2015/lib/cmake/Qt5")

include_directories(${CMAKE_SOURCE_DIR}/includes)

add_subdirectory(src)

