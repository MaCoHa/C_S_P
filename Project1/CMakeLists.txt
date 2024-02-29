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
#SET (CMAKE_CXX_FLAGS "-std=c++20")
add_executable(main ${SOURCES})
#add_executable(count Count_then_move.cpp)
#add_executable(concurrent Concurrent.cpp)
#add_executable(inputGen utils/inputGen.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20 -Ofast")

#if(UNIX AND NOT APPLE)
#    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
 #   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D PERF_TIMEOUT_SERVER -pthread")
 #   set(CMAKE_HAVE_THREADS_LIBRARY 1)
 #   set(CMAKE_USE_WIN32_THREADS_INIT 0)
 #   set(CMAKE_USE_PTHREADS_INIT 1)
 #   set(THREADS_PREFER_PTHREAD_FLAG ON)
#endif()
