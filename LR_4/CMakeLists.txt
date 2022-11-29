cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(main LANGUAGES CXX)
add_executable(main ./src/main.cpp)
add_executable(child ./src/child.cpp)