#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char secretword[20];
char try[26];
int attempts = 0;

void openin() {
    printf("*********************\n");
    printf("** Hangman Game!!! **\n");
    printf("*********************\n\n");
    printf("Try to guess the secret word in 6 errors!\n\n");
}

void list() {
    FILE* f = fopen("list.txt", "r");

    if (f == NULL) {
        printf("Error opening the file!\n");
        exit(1);
    }

    int wordlist;
    fscanf(f, "%d", &wordlist);

    srand(time(0));
    int randomicnum = rand() % wordlist;

    for (int i = 0; i <= randomicnum; i++) {
        fscanf(f, "%s", secretword);
    }

    fclose(f);
}

void draw_hangman(int miss) {
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (miss>=1?'(':' '), (miss>=1?'_':' '), (miss>=1?')':' '));
    printf(" |      %c%c%c  \n", (miss>=4?'\\':' '), (miss>=2?'|':' '), (miss>=3?'/': ' '));
    printf(" |       %c     \n", (miss>=2?'|':' '));
    printf(" |      %c %c   \n", (miss>=6?'/':' '), (miss>=5?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
}

void show_word() {
    for (int i = 0; i < strlen(secretword); i++) {
        int found = 0;
        for (int j = 0; j < attempts; j++) {
            if (try[j] == secretword[i]) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("%c ", secretword[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n\n");
}

int is_wrong(char letter) {
    for (int i = 0; i < strlen(secretword); i++) {
        if (secretword[i] == letter) {
            return 0;
        }
    }
    return 1;
}

void trye() {
    char kick;
    printf("Enter a letter: ");
    scanf(" %c", &kick);
    printf("\n--------------------\n");

    try[attempts] = kick;
    attempts++;
}

int main() {
    openin();
    list();

    int miss = 0;
    int win = 0;
    int max_errors = 6;

    do {
        draw_hangman(miss);
        show_word();
        trye();

        if (is_wrong(try[attempts - 1])) {
            miss++;
        }

        win = 1;
        for (int i = 0; i < strlen(secretword); i++) {
            int found = 0;
            for (int j = 0; j < attempts; j++) {
                if (try[j] == secretword[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                win = 0;
                break;
            }
        }

    } while (!win && miss < max_errors);

    if (win) {
        printf("Congratulations! You've guessed the word: %s\n", secretword);
    } else {
        draw_hangman(miss);
        printf("Sorry, you've been hanged. The word was: %s\n", secretword);
    }

    return 0;
}

