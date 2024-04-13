#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    char *input;

    // Initialize Readline
    rl_bind_key('\t', rl_complete);

    // Display prompt
    printf("Enter a command: ");

    // Signal the start of a new line
    rl_on_new_line();

    // Read input
    input = readline("");

    // Add input to history
    add_history(input);

    // Process input
    printf("You entered: %s\n", input);

    // Free memory
    free(input);

    return 0;
}
