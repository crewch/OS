cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(main LANGUAGES CXX)

add_executable(main ./src/main.cpp)
target_link_libraries(main zmq)

add_executable(node ./src/node.cpp)
target_link_libraries(node zmq)