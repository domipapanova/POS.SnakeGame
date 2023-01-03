cmake_minimum_required(VERSION 3.18)
project(SnakeGame)
set(CMAKE_CXX_STANDARD 14)

add_executable(SnakeGame main.cpp Grid.h Grid.cpp Game.cpp Game.h Snake.cpp Snake.h)
target_link_libraries(SnakeGame pthread)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)

target_link_libraries(SnakeGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)