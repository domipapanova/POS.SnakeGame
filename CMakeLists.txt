cmake_minimum_required(VERSION 3.15)
project(SnakeGame)
set(CMAKE_CXX_STANDARD 14)
#find_library(C:\\Program Files \(x86\)\\Windows Kits\\10\\Source\\10.0.22621.0 conio.h)
#target_link_libraries(SnakeGame conio.h)
#find_package(WindowsSDK REQUIRED)
#include_directories(${WindowsSDK_INCLUDE_DIRS})

add_executable(SnakeGame main.cpp Grid.h Grid.cpp Game.cpp Game.h Snake.cpp Snake.h Client.h Client.cpp Server.cpp Server.h Output.cpp Output.h Consts.h)
target_link_libraries(SnakeGame pthread)

