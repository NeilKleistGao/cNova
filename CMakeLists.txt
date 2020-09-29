cmake_minimum_required(VERSION 3.17)
project(cNova)

set(CMAKE_CXX_STANDARD 17)

add_executable(cNova main.cpp lexical/token.h lexical/operator.h lexical/keyword.h lexical/dfa.h lexical/constant.h)