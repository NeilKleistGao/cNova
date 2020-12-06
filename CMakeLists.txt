cmake_minimum_required(VERSION 3.10)
project(cNova)

set(CMAKE_CXX_STANDARD 11)

add_executable(cNova test/test_LR_io.cc
        gramma/LR_io.hpp
)