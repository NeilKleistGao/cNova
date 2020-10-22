cmake_minimum_required(VERSION 3.10)
project(cNova)

set(CMAKE_CXX_STANDARD 17)

add_executable(cNova test/lexical_test.cc
        lexical/lexical_definition.h
        io/input_stream.h io/input_stream.cc
        lexical/lexical_converter.cc
        lexical/lexical_converter.h lexical/lexical_exceptions.h lexical/lexical_exceptions.cc io/io_exceptions.h io/io_exceptions.cc)