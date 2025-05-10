#include <stdio.h>
#include <stdint.h>
#include "include/feistel.h"

int main() {
    printf("=== Feistel Cipher Encryption ===\n");

    uint16_t plaintext = get_validated_input("Enter a 16-bit plaintext (0 - 65535): ", 0, 65535);
    uint8_t key = get_validated_input("Enter an 8-bit key (0 - 255): ", 0, 255);

    uint16_t encrypted = feistel_encrypt(plaintext, key);
    printf("Encrypted: %u\n", encrypted);

    uint16_t decrypted = feistel_decrypt(encrypted, key);
    printf("Decrypted: %u\n", decrypted);

    if (decrypted != plaintext) {
        fprintf(stderr, "Decryption failed. Data mismatch!\n");
        return 1;
    } else {
        printf("Decryption successful. Original and decrypted data match.\n");
    }

    return 0;
}
