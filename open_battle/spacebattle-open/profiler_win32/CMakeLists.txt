cmake_minimum_required(VERSION 3.17)
project(profiler_win32)

set(CMAKE_CXX_STANDARD 17)

add_executable(profiler_win32 Profiler.cpp ../engine/Engine.cpp)