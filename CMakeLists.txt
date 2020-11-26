cmake_minimum_required( VERSION 3.0 )

project(lab4)

include_directories( ./src ./test ./include)

add_executable(test ./test/main.cpp ./src/matrix.cpp ./include/matrix.hpp)