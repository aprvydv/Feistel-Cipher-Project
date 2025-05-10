#ifndef FEISTEL_H
#define FEISTEL_H

#include <stdint.h>

#define ROUNDS 8

uint16_t feistel_encrypt(uint16_t plaintext, uint8_t master_key);
uint16_t feistel_decrypt(uint16_t ciphertext, uint8_t master_key);
int get_validated_input(const char* prompt, int min, int max);

#endif
