cmake_minimum_required(VERSION 3.27)
project(chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(Chess)

add_executable(chess
        Chess/chess.cpp
        Chess/chess.h
        Chess/main.cpp)
