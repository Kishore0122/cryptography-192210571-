#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 8

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}
void des_encrypt_block(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    memcpy(ciphertext, plaintext, BLOCK_SIZE); 
}

void triple_des_encrypt_block(uint8_t *plaintext, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *ciphertext) {
    uint8_t temp1[BLOCK_SIZE];
    uint8_t temp2[BLOCK_SIZE];

    des_encrypt_block(plaintext, key1, temp1);
    des_encrypt_block(temp1, key2, temp2);
    des_encrypt_block(temp2, key3, ciphertext);
}

void cbc_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t block[BLOCK_SIZE];
    uint8_t prev_ciphertext[BLOCK_SIZE];
    memcpy(prev_ciphertext, iv, BLOCK_SIZE);

    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        xor_blocks(&plaintext[i], prev_ciphertext, block);
        triple_des_encrypt_block(block, key1, key2, key3, &ciphertext[i]);
        memcpy(prev_ciphertext, &ciphertext[i], BLOCK_SIZE);
    }
}

int main() {
    uint8_t key1[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t key2[BLOCK_SIZE] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    uint8_t key3[BLOCK_SIZE] = {0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t plaintext[16] = "Hello, CBC Mode";
    uint8_t ciphertext[16];

    cbc_encrypt(plaintext, sizeof(plaintext), key1, key2, key3, iv, ciphertext);

    printf("Ciphertext:\n");
    for (int i = 0; i < sizeof(ciphertext); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}