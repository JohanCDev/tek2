cmake_minimum_required(VERSION 3.17.0)

project(hello)
set(CMAKE_C_STANDARD_REQUIRED 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

find_package(Criterion REQUIRED)
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)