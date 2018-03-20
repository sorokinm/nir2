#include <stdlib.h>
#include <stdio.h>
#include "integral_properties_check.h"

#define BLOCKS_IN_SET 256

unsigned char** generate_set_with_one_A_prop(unsigned place_of_A, unsigned char_num, unsigned char c) {

    unsigned char** res = (unsigned char**) malloc(256 * sizeof(unsigned char*));
    for (int i = 0; i < 256; i++) {
        res[i] = (unsigned char*) malloc(char_num * sizeof(unsigned char));
        for (int j = 0; j < char_num; ++j) {
            if (j == place_of_A) {
                res[i][j] = (unsigned char)i;
            } else {
                res[i][j] = c;
            }
        }
    }
    return res;
}

char determine_integral_property(int place, unsigned char** blocks) {
    unsigned char * set = NULL;
    set = (unsigned char*) malloc(BLOCKS_IN_SET * sizeof(unsigned char));

    for (int block = 0; block < BLOCKS_IN_SET; ++block) {
        set[block] = blocks[block][place];
    }
    if (is_all(set, 256)) {
        free(set);
        return 'A';
    } else if (is_constant(set, 256)) {
        free(set);
        return 'C';
    } else if (is_zerosum(set, 256)) {
        free(set);
        return 'S';
    } else {
        free(set);
        return 'U'; // unknown
    }
}




void sort(unsigned char* arr, int length) {
    int is_swap = 0;
    for (int i = 0; i < length - 1; ++i) {
        is_swap = 0;
        for (int j = 0; j < length - i - 1; ++j) {
            if (arr[j] > arr[j + 1]){
                unsigned char tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                is_swap = 1;
            }
        }
        if (is_swap == 0) {
            break;
        }
    }
}

int is_constant(unsigned char* set, int size) {
    sort(set, size);
    unsigned char l = set[0];
    for (int i = 1; i < size; ++i) {
        if (set[i] != l) {
            return 0; // false
        }
    }
    return 1; // true
}

int is_all(unsigned char* set, int size) {
    unsigned char prev = set[0];
    for (int i = 1; i < size; ++i) {
        if (set[i] != prev + 1) {
            return 0; // false
        }
        prev = set[i];
    }
    return 1; // true
}

int is_zerosum(unsigned char* set, int size) {
    unsigned char res = set[0];
    for (int i = 1; i < size; ++i) {
        res ^= set[i];
    }
    if (res == 0) {
        return 1; // true
    } else {
        return 0; //false
    }
}

void free_set(unsigned char** set) {
    for (int i = 0; i < 256; ++i) {
        free(set[i]);
    }
    free(set);
}

void print_vector_of_properties(unsigned char** blocks, unsigned char_num) {
    for (int i = 0; i < char_num; ++i) {
        printf("%c ", determine_integral_property(i, blocks));
    }
    printf("\n");
}

