#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 8
void des_encrypt_block(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    memcpy(ciphertext, plaintext, BLOCK_SIZE); 
}
void des_decrypt_block(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    memcpy(plaintext, ciphertext, BLOCK_SIZE); 
}
void ecb_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *ciphertext) {
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        des_encrypt_block(&plaintext[i], key, &ciphertext[i]);
    }
}
void ecb_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *plaintext) {
    for (int i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        des_decrypt_block(&ciphertext[i], key, &plaintext[i]);
    }
}

int main() {
    uint8_t plaintext[] = "0123456789ABCDEF0123456789ABCDEF";
    uint8_t key[] = "1234567890ABCDEF";
    uint8_t ciphertext[sizeof(plaintext)];
    uint8_t decrypted_plaintext[sizeof(plaintext)];

    ecb_encrypt(plaintext, sizeof(plaintext), key, ciphertext);

    ciphertext[0] ^= 0x01; 

    ecb_decrypt(ciphertext, sizeof(ciphertext), key, decrypted_plaintext);

    printf("Original plaintext: %s\n", plaintext);
    printf("Modified ciphertext: ");
    for (int i = 0; i < sizeof(ciphertext); i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted plaintext: %s\n", decrypted_plaintext);

    return 0;
}