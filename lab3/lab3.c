#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_word_to_history(char *history[], int *total, char *input) {
    int i = *total % 5;

    free(history[i]);
    history[i] = strdup(input);
    (*total)++;
}

void print_history(char *history[], int *total) {
    int start = 0;
    int num_to_print = *total;

    if (*total > 5) {
        start = *total % 5;
        num_to_print = 5;
    }

    for (int i = 0; i < num_to_print; i++) {
        printf("%s", history[(start + i) % 5]);
    }
}

int main(void) {
    char *history[5] = {NULL};
    char *input = NULL;
    size_t size = 0;
    int total = 0;

    while (1) {
        printf("Enter input: ");

        if (getline(&input, &size, stdin) == -1) {
            break;
        }

        add_word_to_history(history, &total, input);

        if (strcmp("print\n", input) == 0) {
            print_history(history, &total);
        }
    }

    free(input);

    for (int i = 0; i < 5; i++) {
        free(history[i]);
    }

    return 0;
}
