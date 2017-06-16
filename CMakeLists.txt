cmake_minimum_required(VERSION 3.7)
project(ia_simulatedAnnealing)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SimulatedAnnealing.cpp SimulatedAnnealing.h)
add_executable(ia_simulatedAnnealing ${SOURCE_FILES} SimulatedAnnealing.cpp SimulatedAnnealing.h)