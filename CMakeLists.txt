cmake_minimum_required(VERSION 3.28)
project(ConsoleEngine_v2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConsoleEngine_v2 main.cpp
        Engine/ConsoleEngine.cpp
        Engine/ConsoleEngine.h
        Engine/Core/Window/Window.cpp
        Engine/Core/Window/Window.h)
