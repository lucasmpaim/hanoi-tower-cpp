cmake_minimum_required(VERSION 3.20)
project(hanoiOfTower)

set(CMAKE_CXX_STANDARD 17)

add_executable(hanoiOfTower main.cpp Stack/Stack.h Tower/Tower.cpp Tower/Tower.h Game/Game.cpp Game/Game.h)
