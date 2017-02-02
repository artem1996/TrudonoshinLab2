cmake_minimum_required(VERSION 3.6)
project(arinatrud2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp gauss.cpp gauss.h equation.cpp equation.h boundarycondition.cpp boundarycondition.h UnEvenStep.cpp UnEvenStep.h)
add_executable(arinatrud2 ${SOURCE_FILES})