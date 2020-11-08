cmake_minimum_required(VERSION 3.14)
project(si)

set(CMAKE_CXX_STANDARD 17)

add_executable(si
        main.cpp Set.h NFA.h DFA.h DFA.cpp NFA.cpp)
