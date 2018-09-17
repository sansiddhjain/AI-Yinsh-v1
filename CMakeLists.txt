cmake_minimum_required(VERSION 3.8)
project(yinsh_ai)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")

add_executable(yinsh_ai main.cpp Board.cpp Board.h Agent.cpp Agent.h)
add_executable(test test.cpp Board.cpp Board.h Agent.cpp Agent.h)
