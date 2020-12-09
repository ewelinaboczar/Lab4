cmake_minimum_required( VERSION 3.0 )

project(lab4)

include_directories( ./src ./include)

add_executable(test ./src/main.cpp ./src/matrix.cpp )