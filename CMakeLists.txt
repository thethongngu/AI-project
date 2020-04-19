cmake_minimum_required(VERSION 3.15)
project(main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main main.cpp Board.cpp Board.h Game.cpp Game.h Player.cpp Player.h AlphaBetaTree.cpp AlphaBetaTree.h Node.cpp Node.h)