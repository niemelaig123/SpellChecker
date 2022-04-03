cmake_minimum_required(VERSION 3.17)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment_3
        src/main.cpp src/Dictionary.cpp src/Dictionary.h src/Word.cpp src/Word.h src/SpellChecker.cpp src/SpellChecker.h)
