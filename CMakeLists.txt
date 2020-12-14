cmake_minimum_required(VERSION 3.10)
project(cNova)

set(CMAKE_CXX_STANDARD 17)

add_executable(quick-power
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
        vm/cnova_interpreter.h vm/cnova_vm.h examples/quick_power.cc cnova.h vm/cnova_vm.cc vm/cnova_self.h vm/cnova_interpreter.cc vm/runtime_exception.h clib/libs.h clib/string_lib.cc)