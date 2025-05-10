#include <assert.h>
#include <stdint.h>
#include "../include/feistel.h"

int main() {
    uint16_t pt = 12345;
    uint8_t key = 42;
    uint16_t ct = feistel_encrypt(pt, key);
    uint16_t dt = feistel_decrypt(ct, key);
    assert(pt == dt);
    return 0;
}
