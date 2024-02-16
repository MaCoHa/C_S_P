cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project (project)
set(SOURCES
    main.cpp
    Concurrent.cpp
    utils/inputGen.cpp
)
SET (CMAKE_CXX_FLAGS "-std=c++20")
add_executable(main ${SOURCES})
#add_executable(count Count_then_move.cpp)
#add_executable(concurrent Concurrent.cpp)
#add_executable(inputGen utils/inputGen.cpp)

