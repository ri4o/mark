#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

char* reverse(const char*text){
    if (text==NULL)
        return NULL;
    int lenght = strlen(text);
    char* reversed= (char*) malloc((lenght + 1)* sizeof(char));
    if (reversed ==NULL)
        return NULL;
    for (int i=0; i<lenght; i++){
        reversed[i]= islower(text[lenght-i-1]) ? toupper(text[lenght-i-1]) : text[lenght-i-1];
    }
    reversed[lenght]='\0';
    return reversed;
}


char* vigenere_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) {
        return NULL;
    }

    int key_length = strlen(key);
    int text_length = strlen(text);
    char* encrypted_text = (char*)malloc((text_length + 1) * sizeof(char));
    if (encrypted_text == NULL) {
        return NULL;
    }
    for (int i = 0, j = 0; i < text_length; i++) {
        char current_char = text[i];
        char key_char = toupper(key[j % key_length]);
        char encrypted_char;

        if (isalpha(current_char)) {
            char base = isupper(current_char) ? 'A' : 'a';
            encrypted_char = base + (current_char - base + key_char - 'A') % 26;
            j++;
        } else {
            encrypted_char = current_char;
        }

        encrypted_text[i] = encrypted_char;
    }
    encrypted_text[text_length] = '\0';

    return encrypted_text;
}
char* vigenere_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) {
        return NULL;
    }

    int key_length = strlen(key);
    int text_length = strlen(text);
    char* decrypted_text = (char*)malloc((text_length + 1) * sizeof(char));
    if (decrypted_text == NULL) {
        return NULL;
    }
    for (int i = 0, j = 0; i < text_length; i++) {
        char current_char = text[i];
        char key_char = toupper(key[j % key_length]);
        char decrypted_char;

        if (isalpha(current_char)) {
            char base = isupper(current_char) ? 'A' : 'a';
            decrypted_char = base + (current_char - key_char + 26) % 26;
            j++;
        } else {
            decrypted_char = current_char;
        }

        decrypted_text[i] = decrypted_char;
    }
    decrypted_text[text_length] = '\0';

    return decrypted_text;
}

int main() {
    const char* input = "Hello world!";
    char* reversed = reverse(input);
    if (reversed != NULL) {
        printf("%s\n", reversed);
        free(reversed);
    } else {
        printf("Input is NULL.\n");
    }
    return 0;
}