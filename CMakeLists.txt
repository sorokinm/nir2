cmake_minimum_required(VERSION 3.7)
project(nir2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp picaro/round_function.c)
add_executable(nir2 ${SOURCE_FILES})