cmake_minimum_required(VERSION 3.18)
project(SnakeGame)
set(CMAKE_CXX_STANDARD 14)

add_executable(SnakeGame main.cpp server.cpp server.h client.cpp client.h)
target_link_libraries(SnakeGame pthread)