cmake_minimum_required(VERSION 3.18)
project(SnakeGame)
set(CMAKE_CXX_STANDARD 14)

add_executable(SnakeGame main.cpp Grid.h Grid.cpp Game.cpp Game.h Snake.cpp Snake.h Client.h Client.cpp Server.cpp Server.h)
target_link_libraries(SnakeGame pthread)
