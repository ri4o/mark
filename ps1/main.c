#include <stdio.h>
#include <stdlib.h>
#include "playfair.h"


int main() {
    char *encrypted, *decrypted;
    encrypted = playfair_encrypt("SeCReT", "Hello world");
    printf("%s\n", encrypted);
    decrypted = playfair_decrypt("SeCReT", encrypted);
    printf("%s\n", decrypted);
    free(encrypted);
    free(decrypted);
    encrypted = playfair_encrypt("world", "Hello");
    printf("%s\n", encrypted);
    decrypted = playfair_decrypt("world", encrypted);
    printf("%s\n", decrypted);
    free(encrypted);
    free(decrypted);
    encrypted = playfair_encrypt("Password", "Taxi please");
    printf("%s\n", encrypted);
    decrypted = playfair_decrypt("Password", encrypted);
    printf("%s\n", decrypted);
    free(encrypted);
    free(decrypted);
    encrypted = playfair_encrypt("please", "Taxxxiii");
    printf("%s\n", encrypted);
    decrypted = playfair_decrypt("please", encrypted);
    printf("%s\n", decrypted);
    free(encrypted);
    free(decrypted);
    return 0;
}
