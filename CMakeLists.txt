cmake_minimum_required(VERSION 3.10)
project(cpp_learning)

# Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB week1_sources week1/*.cpp)
add_executable(week1 ${week1_sources})
