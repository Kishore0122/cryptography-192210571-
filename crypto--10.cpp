#include <stdio.h>
#include <string.h>
void print_hex(unsigned char *array, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", array[i]);
    }
}
int main() {
    SHA_CTX ctx;
    unsigned char hash[SHA_DIGEST_LENGTH];
    char input[] = "";
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, input, strlen(input));
    SHA1_Final(hash, &ctx);
    printf("SHA1(\"%s\") = ", input);
    print_hex(hash, SHA_DIGEST_LENGTH);
    printf("\n");
    char input2[] = "abc";
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, input2, strlen(input2));
    SHA1_Final(hash, &ctx);
    printf("SHA1(\"%s\") = ", input2);
    print_hex(hash, SHA_DIGEST_LENGTH);
    printf("\n");
    char input3[] = "abcdefghijklmnopqrstuvwxyz";
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, input3, strlen(input3));
    SHA1_Final(hash, &ctx);
    printf("SHA1(\"%s\") = ", input3);
    print_hex(hash, SHA_DIGEST_LENGTH);
    printf("\n");
    return 0;
}
