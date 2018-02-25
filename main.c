#include <stdio.h>
#include <stdlib.h>
#include "picaro/picaro_cipher.h"

#define ROUND_NUM 12
#define KEY_SIZE 14

unsigned char** fake_key_generator(int round_number, int key_size_in_bytes, int isRandom);

void free_key_space(unsigned char** buf, int round_number);
void reverse_fake_keys (unsigned char** keys, int round_number);


int main() {
    printf("Hello!\n");
    long a = 0x010203040506;
    long b = 0x0305c31405a637f8;

    unsigned char key[8];
    *((long*)key) = a;

    unsigned char buf[16] = {0};
    *((long*)buf) = a;
    *((long*)(buf + 8)) = b;

    for (int i = 0; i < 16; ++i) {
        printf("%02x ", buf[i]);
    }
    printf("\n");

    unsigned char** keys = fake_key_generator(ROUND_NUM, KEY_SIZE, 1);
    crypt_picaro(buf, keys, ROUND_NUM);
    reverse_fake_keys(keys, ROUND_NUM);

    for (int i = 0; i < 16; ++i) {
        printf("%02x ", buf[i]);
    }
    printf("\n");

    crypt_picaro(buf, keys, ROUND_NUM);

    //round_step(buf, key, 8);
    //swap_parts(buf);
    //round_step(buf, key, 8);
    //swap_parts(buf);

    for (int i = 0; i < 16; ++i) {
        printf("%02x ", buf[i]);
    }
    printf("\n");

    free_key_space(keys, 12);
    return 0;
}


// unsafe. if you're going to copy this, so don't!
unsigned char** fake_key_generator(int round_number, int key_size_in_bytes, int isRandom) {

    unsigned char** res = (unsigned char**) malloc(round_number * sizeof(unsigned char*));
    unsigned char cur_val = 5;
    for (int i = 0; i < round_number; ++i) {
        res[i] = (unsigned char*) malloc(key_size_in_bytes * sizeof(unsigned char));
        for (int j = 0; j < key_size_in_bytes; ++j) {
            if (isRandom == 1) {
                res[i][j] = (unsigned char) rand();
            } else {
                res[i][j] = cur_val;
                cur_val = (unsigned char)(5 * cur_val + 197);
            }
        }
    }
    return res;
}

void free_key_space(unsigned char** buf, int round_number) {
    for (int i = 0; i < round_number; ++i) {
        free(buf[i]);
    }
    free(buf);
}

void reverse_fake_keys (unsigned char** keys, int round_number) {
    unsigned char tmp = 0;
    for (int i = 0; i < round_number / 2; i++) {
        for (int j = 0; j < KEY_SIZE; ++j) {
            tmp = keys[i][j];
            keys[i][j] = keys[round_number - i - 1][j];
            keys[round_number - i - 1][j] = tmp;
        }
    }
}