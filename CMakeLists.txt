cmake_minimum_required(VERSION 3.10)
project(tradutor)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES src/main.cpp src/io_file.cpp src/translator.cpp)
set(INCL_FILES include/io_file.hpp include/console.hpp include/translator.hpp include/defs.hpp)

add_executable(tradutor ${INCL_FILES} ${SRC_FILES})