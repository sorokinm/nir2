#ifndef NIR2_PICARO_CIPHER_H
#define NIR2_PICARO_CIPHER_H

void round_step(unsigned char* double_vector, unsigned char* round_key, unsigned key_size);
void swap_parts(unsigned char* buffer);
void crypt_picaro(unsigned char* buffer, unsigned char** keys, unsigned round_number);

#endif //NIR2_PICARO_CIPHER_H
