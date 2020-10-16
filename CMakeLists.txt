cmake_minimum_required(VERSION 3.10)
project(cNova)

set(CMAKE_CXX_STANDARD 14)

add_executable(cNova main.cpp cNova_lex.h  input_stream.h input_stream.cpp util_functions.cpp)