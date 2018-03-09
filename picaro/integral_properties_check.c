#include <stdlib.h>
#include <stdio.h>


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

void free_set(unsigned char** set) {
    for (int i = 0; i < 256; ++i) {
        free(set[i]);
    }
    free(set);
}

