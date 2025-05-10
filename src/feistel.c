#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/feistel.h"

static uint8_t sbox[16] = { 0xC, 0x5, 0x6, 0xB, 0x9, 0x0, 0xA, 0xD, 0x3, 0xE, 0xF, 0x8, 0x4, 0x7, 0x1, 0x2 };
static uint8_t pbox[8] = {2, 4, 6, 0, 7, 1, 3, 5};

static uint8_t rotate_left(uint8_t value, int shift) {
    return (value << shift) | (value >> (8 - shift));
}

static void generate_round_keys(uint8_t master_key, uint8_t round_keys[ROUNDS]) {
    for (int i = 0; i < ROUNDS; i++) {
        round_keys[i] = rotate_left(master_key, i);
    }
}

static uint8_t apply_pbox(uint8_t value) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        if (value & (1 << i)) {
            result |= (1 << pbox[i]);
        }
    }
    return result;
}

static uint8_t round_function(uint8_t half, uint8_t key) {
    uint8_t x = half ^ key;
    uint8_t upper = sbox[(x >> 4) & 0x0F];
    uint8_t lower = sbox[x & 0x0F];
    uint8_t sbox_out = (upper << 4) | lower;
    return apply_pbox(sbox_out);
}

uint16_t feistel_encrypt(uint16_t plaintext, uint8_t master_key) {
    uint8_t left = (plaintext >> 8) & 0xFF;
    uint8_t right = plaintext & 0xFF;
    uint8_t round_keys[ROUNDS];
    generate_round_keys(master_key, round_keys);

    for (int i = 0; i < ROUNDS; i++) {
        uint8_t temp = right;
        right = left ^ round_function(right, round_keys[i]);
        left = temp;
    }

    return ((uint16_t)left << 8) | right;
}

uint16_t feistel_decrypt(uint16_t ciphertext, uint8_t master_key) {
    uint8_t left = (ciphertext >> 8) & 0xFF;
    uint8_t right = ciphertext & 0xFF;
    uint8_t round_keys[ROUNDS];
    generate_round_keys(master_key, round_keys);

    for (int i = ROUNDS - 1; i >= 0; i--) {
        uint8_t temp = left;
        left = right ^ round_function(left, round_keys[i]);
        right = temp;
    }

    return ((uint16_t)left << 8) | right;
}

int get_validated_input(const char* prompt, int min, int max) {
    long value;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            fprintf(stderr, "Error reading input.\n");
            exit(EXIT_FAILURE);
        }

        if (strchr(buffer, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long. Please enter a shorter value.\n");
            continue;
        }

        char *endptr;
        value = strtol(buffer, &endptr, 10);
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            printf("Invalid input. Please enter a valid number.\n");
            continue;
        }

        if (value < min || value > max) {
            printf("Input must be between %d and %d.\n", min, max);
            continue;
        }

        break;
    }
    return (int)value;
}
