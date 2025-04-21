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
    printf("Try to guess the secret word in 12 attempts!\n\n");
}

void list() {
    FILE* f;
    f = fopen("list.txt", "r");

    if (f == NULL) {
        printf("Error to open the file!\n");
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

void trye() {
    char kick;
    printf("Enter a letter: ");
    scanf(" %c", &kick); 

    try[attempts] = kick; 
    attempts++; 
}

int check(int i) {
    for (int j = 0; j < attempts; j++) {
        if (try[j] == secretword[i]) {
            return 1; 
        }
    }
    return 0; 
}

void output(int i) {
    if (check(i)) {
        printf("%c", secretword[i]); 
    } else {
        printf("_ "); 
    }
}

int main() {
    openin();
    list(); 
    int righ = 0;
    int miss = 0;
    int max_attempts = 12;

    do {
        for (int i = 0; i < strlen(secretword); i++) {
            output(i);
        }
        printf("\n");

        trye();

        righ = 1;
        for (int i = 0; i < strlen(secretword); i++) {
            if (!check(i)) {
                righ = 0;
                break;
            }
        }

        if (attempts > max_attempts) {
            miss = 1; 
        }

    } while (!righ && !miss); 

    if (righ) {
        printf("Congratulations! You've guessed the word: %s\n", secretword);
    } else {
        printf("Sorry, you've run out of attempts. The word was: %s\n", secretword);
    }

    return 0;
}
