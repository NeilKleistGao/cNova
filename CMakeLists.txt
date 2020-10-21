cmake_minimum_required(VERSION 3.10)
project(cNova)

set(CMAKE_CXX_STANDARD 17)

add_executable(cNova main.cc lexical/lexical_definition.h io/input_stream.h io/input_stream.cc lexical/lexical_converter.cc lexical/lexical_converter.h)