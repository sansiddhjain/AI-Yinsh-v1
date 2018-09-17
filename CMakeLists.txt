cmake_minimum_required(VERSION 3.8)
project(yinsh_ai)

set(CMAKE_CXX_STANDARD 14)

add_executable(yinsh_ai main.cpp Board.cpp Board.h Agent.cpp Agent.h)
