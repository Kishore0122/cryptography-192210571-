#include <stdio.h>
#include <stdint.h>
#define LEFT_ROTATE(val, shift) (((val) << (shift)) | ((val) >> (28 - (shift))))
void generate_subkeys(uint64_t key, uint32_t subkeys[16][2]) {
    uint32_t C = (key >> 28) & 0xFFFFFFF;
    uint32_t D = key & 0xFFFFFFF;
    int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    for (int i = 0; i < 16; i++) {
        C = LEFT_ROTATE(C, shifts[i]) & 0xFFFFFFF;
        D = LEFT_ROTATE(D, shifts[i]) & 0xFFFFFFF;
        subkeys[i][0] = (C >> 4) & 0xFFFFFF; 
        subkeys[i][1] = D & 0xFFFFFF;       
    }
}
void print_subkeys(uint32_t subkeys[16][2]) {
    for (int i = 0; i < 16; i++) {
        printf("Subkey %2d: %06X %06X\n", i + 1, subkeys[i][0], subkeys[i][1]);
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1; 
    uint32_t subkeys[16][2];

    generate_subkeys(key, subkeys);
    print_subkeys(subkeys);

    return 0;
}