#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    char playAgain[4];

    do {
        printf("*********************************\n");
        printf("** Welcome to Guess The Number **\n");
        printf("*********************************\n\n");
        printf("Try to guess the number between 1 and 100. Good luck!\n\n");
        printf("You have three types of difficulty:\n");
        printf(" (1) Easy - fifteen attempts.\n");
        printf(" (2) Medium - ten attempts.\n");
        printf(" (3) Difficult - five attempts.\n");
        printf("Type the difficulty number you would like: ");

        int choice;
        scanf("%d", &choice);

        int maxAttempts;
        switch (choice) {
            case 1:
                maxAttempts = 15;
                break;
            case 2:
                maxAttempts = 10;
                break;
            case 3:
                maxAttempts = 5;
                break;
            default:
                printf("Invalid choice. Defaulting to Medium difficulty.\n");
                maxAttempts = 10;
                break;
        }

        srand(time(NULL));
        int secretNumber = rand() % 100 + 1;
        int guess;
        int won = 0;

        for (int attempt = 1; attempt <= maxAttempts; attempt++) {
            printf("(For trial version only) the secret number is %d", secretNumber);
            printf("\nAttempt %d of %d. Enter your guess: ", attempt, maxAttempts);
            scanf("%d", &guess);

            if (guess < 1 || guess > 100) {
                printf("Invalid value. Please enter a number between 1 and 100.\n");
                attempt--;
                continue;
            }

            if (guess > secretNumber) {
                printf("Too high! Try a smaller number.\n");
            } else if (guess < secretNumber) {
                printf("Too low! Try a larger number.\n");
            } else {
                printf("Congratulations! You guessed the number!\n");
                won = 1;
                break;
            }
        }

        if (!won) {
            printf("\nSorry, you've used all attempts. The number was %d.\n", secretNumber);
        }

        printf("\nDo you want to play again? (y/n): ");
        scanf("%s", playAgain);
        printf("\n\n-----------------------------------\n\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

    } while (strcmp(playAgain, "n") != 0 && strcmp(playAgain, "N") != 0);

    printf("Thanks for playing!\n");
    return 0;
}
