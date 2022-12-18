cmake_minimum_required(VERSION 3.8)

project(lab5)
include_directories(include)

add_library(lib1 SHARED src/functions1.c)
add_library(lib2 SHARED src/functions2.c)

add_executable(test11 src/test1.c include/functions.h)
add_executable(test12 src/test1.c include/functions.h)
target_link_libraries(test11 lib1)
target_link_libraries(test12 lib2)

if (NOT (DEFINED LIB_PRINT_TYPE))
	set(LIB_PRINT_TYPE DEFAULT)
endif ()

if (LIB_PRINT_TYPE STREQUAL EXTENDED)
	add_compile_definitions(SYSTEM="${CMAKE_SYSTEM}")
elseif (NOT (LIB_PRINT_TYPE STREQUAL DEFAULT))
	message(FATAL_ERROR "Unexpected LIB_PRINT_TYPE: ${LIB_PRINT_TYPE}")
endif ()

add_executable(test2 src/test2.c)
target_link_libraries(test2 ${CMAKE_DL_LIBS})