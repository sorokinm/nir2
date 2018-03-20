//
// Created by hp on 25.02.18.
//

#ifndef NIR2_INTEGRAL_PROPERTIES_CHECK_H
#define NIR2_INTEGRAL_PROPERTIES_CHECK_H

unsigned char** generate_set_with_one_A_prop(unsigned place_of_A, unsigned char_num, unsigned char c);
void free_set(unsigned char** set);
char determine_integral_property(int place, unsigned char** blocks);
void sort(unsigned char* arr, int length);
int is_constant(unsigned char* set, int size);
int is_all(unsigned char* set, int size);
int is_zerosum(unsigned char* set, int size);
void print_vector_of_properties(unsigned char** blocks, unsigned char_num);


#endif //NIR2_INTEGRAL_PROPERTIES_CHECK_H
