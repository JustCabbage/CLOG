cmake_minimum_required(VERSION 3.0.0)
project(CLOG VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

add_executable(CLOG Tests.cpp)
target_include_directories(CLOG PUBLIC include)
