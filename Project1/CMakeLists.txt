cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project (handin)
set(SOURCES
    main.cpp
    Concurrent.cpp
    CountThenMove.cpp
    utils/inputGen.cpp
    includes/Concurrent.hpp
    includes/CountThenMove.hpp
)
add_executable(main ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20 -Ofast")