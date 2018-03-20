cmake_minimum_required(VERSION 3.7)
project(nir2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c picaro/round_function.c picaro/matrices.h picaro/sbox_picaro.h  picaro/galois_arithmetics.c picaro/galois_arithmetics.h picaro/picaro_cipher.h picaro/picaro_key_generation.c picaro/integral_properties_check.c picaro/integral_properties_check.h)
add_executable(nir2 ${SOURCE_FILES})