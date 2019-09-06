cmake_minimum_required(VERSION 3.14)
project(l_system_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(l_system_parser main.cpp Lexer.cpp Lexer.h Token.h Parser.cpp Parser.h Rule.h Engine.cpp Engine.h)