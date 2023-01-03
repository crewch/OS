cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(main LANGUAGES CXX)

add_executable(a.out ./src/main.cpp)
target_link_libraries(a.out zmq)

add_executable(node ./src/node.cpp)
target_link_libraries(node zmq)