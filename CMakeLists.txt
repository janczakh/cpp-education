cmake_minimum_required(VERSION 3.10)
project(cpp_learning)

# Require modern C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB week2_sources week2/*.cpp)
add_executable(week2 ${week2_sources})

file(GLOB week3_sources week3/*.cpp)
add_executable(week3 ${week3_sources})

file(GLOB week4_sources week4/*.cpp)
add_executable(week4 ${week4_sources})

file(GLOB week5_sources week5/*.cpp)
add_executable(week5 ${week5_sources})
