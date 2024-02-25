#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

char* unique_reverse(const char*text){
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
int main(){
    const char* input = "Hello world!";
    char* reversed = unique_reverse(input);
    if(reversed !=NULL){
        printf("%s\n", reversed);
        free(reversed);
    }
    else{
        printf("Input is NULL.\n");
    }
    return 0;
}