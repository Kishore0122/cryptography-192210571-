#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encipher();
void decipher();

int main() {
    int choice;
    
    while(1) {
        printf("\n1. Encrypt Text");
        printf("\t2. Decrypt Text");
        printf("\t3. Exit");
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                encipher();
                break;
            case 2:
                decipher();
                break;
            case 3:
                return 0;
            default:
                printf("Please Enter Valid Option.");
        }
    }
}

void encipher() {
    unsigned int i, j;
    char input[50], key[10];
    
    printf("\nEnter Plain Text: ");
    scanf("%s", input);
    printf("Enter Key Value: ");
    scanf("%s", key);
    
    printf("\nResultant Cipher Text: ");
    for(i = 0, j = 0; i < strlen(input); i++, j++) {
        if(j >= strlen(key))
            j = 0;
        printf("%c", 'A' + (((toupper(input[i]) - 'A') + (toupper(key[j]) - 'A')) % 26));
    }
}

void decipher() {
    unsigned int i, j;
    char input[50], key[10];
    int value;
    
    printf("\nEnter Cipher Text: ");
    scanf("%s", input);
    printf("Enter the Key Value: ");
    scanf("%s", key);
    
    printf("\nDeciphered Plain Text: ");
    for(i = 0, j = 0; i < strlen(input); i++, j++) {
        if(j >= strlen(key))
            j = 0;
        value = (toupper(input[i]) - 'A') - (toupper(key[j]) - 'A');
        if(value < 0)
            value = value * -1;
        printf("%c", 'A' + (value % 26));
    }
}
