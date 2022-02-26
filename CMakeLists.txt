cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "CNova")
project(${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "settle from environ VCPKG_ROOT")
endif()

include_directories(
	${CMAKE_BINARY_DIR}/config
	${PROJECT_SOURCE_DIR}/src/libs
	)

configure_file(config/ROOT_PATH.h.in config/ROOT_PATH.h)

add_subdirectory(src/examples)
add_subdirectory(src/libs)

# add_executable(quick-power
#         examples/quick_power.cc
#         lexical/lexical_exceptions.h
#         lexical/lexical_exceptions.cc
#         lexical/lexical_definition.h
#         lexical/lexical_converter.h
#         lexical/lexical_converter.cc
#         parser/parser.cc
#         parser/parser.h
#         parser/parser_exceptions.cc
#         parser/parser_exceptions.h
#         io/input_stream.h
#         io/input_stream.cc
#         io/io_exceptions.h
#         io/io_exceptions.cc
#         vm/cnova_interpreter.h
#         vm/cnova_vm.h
#         cnova.h
#         vm/cnova_vm.cc
#         vm/cnova_self.h
#         vm/cnova_interpreter.cc
#         vm/runtime_exception.h
#         clib/libs.h
#         clib/string_lib.cc
#         parser/operators.h
#         parser/operators.cc
#         parser/types.h
#         parser/types.cc
#         clib/dictionary_lib.cc
#         clib/math_lib.cc)

# add_executable(word-counter
#         examples/word_counter.cc
#         lexical/lexical_exceptions.h
#         lexical/lexical_exceptions.cc
#         lexical/lexical_definition.h
#         lexical/lexical_converter.h
#         lexical/lexical_converter.cc
#         parser/parser.cc
#         parser/parser.h
#         parser/parser_exceptions.cc
#         parser/parser_exceptions.h
#         io/input_stream.h
#         io/input_stream.cc
#         io/io_exceptions.h
#         io/io_exceptions.cc
#         vm/cnova_interpreter.h
#         vm/cnova_vm.h
#         cnova.h
#         vm/cnova_vm.cc
#         vm/cnova_self.h
#         vm/cnova_interpreter.cc
#         vm/runtime_exception.h
#         clib/libs.h
#         clib/string_lib.cc
#         parser/operators.h
#         parser/operators.cc
#         parser/types.h
#         parser/types.cc
#         clib/dictionary_lib.cc
#         clib/math_lib.cc)

# add_executable(rotate-matrix
#         examples/rotate_matrix.cc
#         lexical/lexical_exceptions.h
#         lexical/lexical_exceptions.cc
#         lexical/lexical_definition.h
#         lexical/lexical_converter.h
#         lexical/lexical_converter.cc
#         parser/parser.cc
#         parser/parser.h
#         parser/parser_exceptions.cc
#         parser/parser_exceptions.h
#         io/input_stream.h
#         io/input_stream.cc
#         io/io_exceptions.h
#         io/io_exceptions.cc
#         vm/cnova_interpreter.h
#         vm/cnova_vm.h
#         cnova.h
#         vm/cnova_vm.cc
#         vm/cnova_self.h
#         vm/cnova_interpreter.cc
#         vm/runtime_exception.h
#         clib/libs.h
#         clib/string_lib.cc
#         parser/operators.h
#         parser/operators.cc
#         parser/types.h
#         parser/types.cc
#         clib/dictionary_lib.cc
#         clib/math_lib.cc)

# add_executable(calc
#         examples/calc.cc
#         lexical/lexical_exceptions.h
#         lexical/lexical_exceptions.cc
#         lexical/lexical_definition.h
#         lexical/lexical_converter.h
#         lexical/lexical_converter.cc
#         parser/parser.cc
#         parser/parser.h
#         parser/parser_exceptions.cc
#         parser/parser_exceptions.h
#         io/input_stream.h
#         io/input_stream.cc
#         io/io_exceptions.h
#         io/io_exceptions.cc
#         vm/cnova_interpreter.h
#         vm/cnova_vm.h
#         cnova.h
#         vm/cnova_vm.cc
#         vm/cnova_self.h
#         vm/cnova_interpreter.cc
#         vm/runtime_exception.h
#         clib/libs.h
#         clib/string_lib.cc
#         parser/operators.h
#         parser/operators.cc
#         parser/types.h
#         parser/types.cc
#         clib/dictionary_lib.cc
#         clib/math_lib.cc)