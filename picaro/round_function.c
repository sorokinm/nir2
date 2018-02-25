//
// Created by hp on 25.02.18.
//

void key_add(unsigned char * text, unsigned char * key, unsigned size) {
    for (int i = 0; i < size; ++i) {
        text[i] ^= key[i];
    }
}