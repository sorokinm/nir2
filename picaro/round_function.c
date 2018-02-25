#include "sbox_picaro.h"
#include "matrices.h"
#include "galois_arithmetics.h"

#define BUFFER_SIZE 14


void key_add(unsigned char * text, unsigned char * key, unsigned size) {
    for (int i = 0; i < size; ++i) {
        text[i] ^= key[i];
    }
}

int expand_vector(unsigned char* buffer, unsigned buffer_size, unsigned char* vector, unsigned vector_size) {
    if (buffer_size != 14 || vector_size != 8) {
        return -1;
    }

    for (int i = 0 ; i < buffer_size; ++i) {
        unsigned char tmp_res = 0;
        for (int  j = 0; j < vector_size; ++j) {
            tmp_res ^= gmul(vector[j],expand_matrix[j][i], PICARO_MODULO_POLYNOMIAL);
        }
        buffer[i] = tmp_res;
    }
    return 0;
}

void substitution_layer(unsigned char* buffer, unsigned buffer_size) {
    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = sbox_picaro[buffer[i]];
    }
}

int compress_vector(unsigned char* buffer, unsigned buffer_size, unsigned char* vector, unsigned vector_size) {
    if (buffer_size != 8 || vector_size != 14) {
        return  -1;
    }

    for (int i = 0; i < buffer_size; ++i) {
        unsigned char tmp_res = 0;
        for (int j = 0; j < vector_size; ++j) {
            tmp_res ^= gmul(vector[j], compress_matrix[j][i], PICARO_MODULO_POLYNOMIAL);
        }
        buffer[i] = tmp_res;
    }
    return 0;
}

int round_transform(unsigned char* vector, unsigned vector_size, unsigned char* round_key, unsigned key_size) {
    if (vector_size != 8 || key_size != BUFFER_SIZE) {
        return -1;
    }

    unsigned char buffer[BUFFER_SIZE] = {0};

    expand_vector(buffer, BUFFER_SIZE, vector, vector_size);
    key_add(buffer,round_key, key_size);
    substitution_layer(buffer, BUFFER_SIZE);
    compress_vector(vector, vector_size, buffer, BUFFER_SIZE);

    return 0;
}

void round_step(unsigned char* double_vector, unsigned dv_size, unsigned char* round_key, unsigned key_size) {
    unsigned char tmp_buffer[8] = {0};
    for (int i = 0; i < 8; ++i) {
        tmp_buffer[i] = double_vector[i];
    }
    round_transform(tmp_buffer, 8, round_key, key_size);
    for (int i = 0; i < 8; ++i) {
        tmp_buffer[i] ^= double_vector[i + 8];
        double_vector[i + 8] = double_vector[i];
        double_vector[i] = tmp_buffer[i];
    }
}
