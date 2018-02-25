cmake_minimum_required(VERSION 3.7)
project(nir2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c picaro/round_function.c picaro/sbox_picaro.h picaro/picaro_matrices_sbox.h picaro/matrix.h picaro/galois_arithmetics.c picaro/galois_arithmetics.h)
add_executable(nir2 ${SOURCE_FILES})