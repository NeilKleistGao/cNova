cmake_minimum_required(VERSION 3.10)
project(cNova)

set(CMAKE_CXX_STANDARD 17)

add_executable(lexical_test
        lexical/lexical_exceptions.h
        lexical/lexical_exceptions.cc
        lexical/lexical_definition.h
        lexical/lexical_converter.h
        lexical/lexical_converter.cc
        io/input_stream.h
        io/input_stream.cc
        io/io_exceptions.h
        io/io_exceptions.cc
        test/lexical_test.cc
)
add_executable(parser_test
        lexical/lexical_exceptions.h
        lexical/lexical_exceptions.cc
        lexical/lexical_definition.h
        lexical/lexical_converter.h
        lexical/lexical_converter.cc
        parser/parser.cc
        parser/parser.h
        parser/parser_exceptions.cc
        parser/parser_exceptions.h
        io/input_stream.h
        io/input_stream.cc
        io/io_exceptions.h
        io/io_exceptions.cc
        test/parser_test.cc
        )