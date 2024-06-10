#include<stdio.h>
#include<string.h>

int main() {
    unsigned int a[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    unsigned int b[3][3] = {{8, 5, 10}, {21, 8, 21}, {21, 12, 8}};
    int i, j, t = 0;
    unsigned int c[20], d[20];
    char msg[20];

    printf("Enter plain text:\n");
    scanf("%s", msg);

    for(i = 0; i < strlen(msg); i++) {
        c[i] = msg[i] - 'A'; // Subtract 'A' to convert ASCII to integer (0-25)
        printf("%d ", c[i]);
    }

    printf("\nEncrypted Cipher Text: ");
    for(i = 0; i < 3; i++) {
        t = 0;
        for(j = 0; j < 3; j++) {
            t += a[i][j] * c[j];
        }
        d[i] = t % 26; // Modulo 26 operation for alphabetic range
        printf("%c", d[i] + 'A'); // Add 'A' to convert back to ASCII character
    }

    printf("\nDecrypted Cipher Text: ");
    for(i = 0; i < 3; i++) {
        t = 0;
        for(j = 0; j < 3; j++) {
            t += b[i][j] * d[j];
        }
        c[i] = t % 26; // Modulo 26 operation for alphabetic range
        printf("%c", c[i] + 'A'); // Add 'A' to convert back to ASCII character
    }

    printf("\n");
    
    return 0;
}
