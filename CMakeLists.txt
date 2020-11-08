cmake_minimum_required(VERSION 3.14)
project(si)

set(CMAKE_CXX_STANDARD 17)

add_executable(si
        main.cpp
        Misc/Set.h
        FiniteAutomata/NFA/NFA.h
        FiniteAutomata/DFA/DFA.h
        FiniteAutomata/DFA/DFA.cpp
        FiniteAutomata/NFA/NFA.cpp
        FiniteAutomata/include.h
        Misc/debug.h )
