cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project (project)

SET (CMAKE_CXX_FLAGS "-std=c++20")
add_executable(main main.cpp)
#add_executable(count Count_then_move.cpp)
add_executable(concurrent Concurrent.cpp)
add_executable(inputGen utils/inputGen.cpp)

