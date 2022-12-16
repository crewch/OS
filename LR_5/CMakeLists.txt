cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(main LANGUAGES CXX)

add_library(
        lib1 SHARED
        ./include/lib.h
        ./src/lib1.cpp
)
add_library(
        lib2 SHARED
        ./include/lib.h
        ./src/lib2.cpp
)

add_executable(main1 ./src/main1.cpp)
target_include_directories(main1 PRIVATE ./include)
target_link_libraries(main1 PRIVATE lib1 m)

add_executable(main2 ./src/main1.cpp)
target_include_directories(main2 PRIVATE ./include)
target_link_libraries(main2 PRIVATE lib2 m)

add_executable(main ./src/main2.cpp)
# target_include_directories(main PRIVATE ./include m)