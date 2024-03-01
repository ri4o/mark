#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playfair.h"


void create_playfair_matrix(const char* key, char matrix[5][5]) {
    int len = strlen(key);
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (!isalpha(key[i]))
            continue;
        char c = toupper(key[i]);
        if (c == 'W')
            c = 'V';
        int found = 0;
        for (int j = 0; j < index; j++) {
            if (matrix[j / 5][j % 5] == c) {
                found = 1;
                break;
            }
        }
        if (!found) {
            matrix[index / 5][index % 5] = c;
            index++;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'W')
            continue;
        int found = 0;
        for (int j = 0; j < index; j++) {
            if (matrix[j / 5][j % 5] == c) {
                found = 1;
                break;
            }
        }
        if (!found) {
            matrix[index / 5][index % 5] = c;
            index++;
        }
    }
}

char* playfair_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL)
        return NULL;
    int key_len = strlen(key);
    if (key_len == 0)
        return NULL;
    char cleaned_key[100] = {'\0'};
    int cleaned_key_index = 0;
    for (int i = 0; i < key_len; i++) {
        char c = toupper(key[i]);
        if (!isalpha(c) || c == 'W')
            continue;
        if (strchr(cleaned_key, c) == NULL)
            cleaned_key[cleaned_key_index++] = c;
    }
    char matrix[5][5];
    create_playfair_matrix(cleaned_key, matrix);
    int text_len = strlen(text);
    int new_text_len = text_len + text_len / 2 + 1;
    char* new_text = (char*)malloc(new_text_len * sizeof(char));
    if (new_text == NULL)
        return NULL;
    int j = 0;
    char last_char = ' ';
    for (int i = 0; i < text_len; i++) {
        char c = toupper(text[i]);
        if (!isalpha(c) && c != ' ')
            continue;
        if (c == 'W')
            c = 'V';
        if (c == last_char && c != ' ') {
            new_text[j++] = 'X';
            last_char = 'X';
        }
        new_text[j++] = c;
        last_char = c;
    }
    if (j % 2 != 0)
        new_text[j++] = 'X';
    new_text[j] = '\0';
    int indexp = 0;
    for (int i = 0; i < j; i += 2) {
        char a = new_text[i];
        char b = new_text[i + 1];
        int a_row, a_col, b_row, b_col;
        // Nájdenie pozícií písmen v matici
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (matrix[row][col] == a) {
                    a_row = row;
                    a_col = col;
                }
                if (matrix[row][col] == b) {
                    b_row = row;
                    b_col = col;
                }
            }
        }
        // Ak sú písmená v rovnakom riadku, posunieme ich o jedno doprava
        if (a_row == b_row) {
            new_text[indexp++] = matrix[a_row][(a_col + 1) % 5];
            new_text[indexp++] = matrix[b_row][(b_col + 1) % 5];

        }
            // Ak sú písmená v rovnakom stĺpci, posunieme ich o jedno dole
        else if (a_col == b_col) {
            new_text[indexp++] = matrix[(a_row + 1) % 5][a_col];
            new_text[indexp++] = matrix[(b_row + 1) % 5][b_col];

        }
            // Inak si vymenia riadky a stĺpce, pričom zostávajú v rovnakom kvadráte
        else {
            new_text[indexp++] = matrix[a_row][b_col];
            new_text[indexp++] = matrix[b_row][a_col];

        }
        if(i != strlen(text)-1) {


            new_text[indexp++] = ' ';
        }
    }

    return new_text;
}


char* playfair_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL)
        return NULL;
    int key_len = strlen(key);
    if (key_len == 0)
        return NULL;

    char cleaned_key[100] = {'\0'};
    int cleaned_key_index = 0;
    for (int i = 0; i < key_len; i++) {
        char c = toupper(key[i]);
        if (!isalpha(c) || c == 'W')
            continue;
        if (strchr(cleaned_key, c) == NULL)
            cleaned_key[cleaned_key_index++] = c;
    }

    char matrix[5][5];
    create_playfair_matrix(cleaned_key, matrix);

    int text_len = strlen(text);
    if (text_len % 2 != 0)
        return NULL;
    char* new_text = (char*)malloc((text_len + 1) * sizeof(char));
    if (new_text == NULL)
        return NULL;
    for (int i = 0; i < text_len; i += 2) {
        char a = text[i];
        char b = text[i + 1];
        int a_row, a_col, b_row, b_col;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (matrix[row][col] == a) {
                    a_row = row;
                    a_col = col;
                }
                if (matrix[row][col] == b) {
                    b_row = row;
                    b_col = col;
                }
            }
        }
        // Ak sú písmená v rovnakom riadku, posunieme ich o jedno doľava
        if (a_row == b_row) {
            new_text[i] = matrix[a_row][(a_col + 4) % 5];
            new_text[i + 1] = matrix[b_row][(b_col + 4) % 5];
        }
            // Ak sú písmená v rovnakom stĺpci, posunieme ich o jedno nahor
        else if (a_col == b_col) {
            new_text[i] = matrix[(a_row + 4) % 5][a_col];
            new_text[i + 1] = matrix[(b_row + 4) % 5][b_col];
        }
        else {
            new_text[i] = matrix[a_row][b_col];
            new_text[i + 1] = matrix[b_row][a_col];
        }
    }
    new_text[text_len] = '\0';
    if (new_text[text_len - 1] == 'X')
        new_text[text_len - 1] = '\0';
    for (int i = 0; i < text_len; i++) {
        if (new_text[i] == 'W') {
            free(new_text);
            return NULL;
        }
    }

    return new_text;
}

