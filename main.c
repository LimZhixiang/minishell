#include "minishell.h"

int main()
{
	char *line;
	line = NULL;
	line = readline("Minishell: ");
	printf("%s", line);
	return 0;
}

// 1. readline()
// 	library: <readline/readline.h>
// 	Inputs: readline("prompt message")
// 	Outputs: char*
dishdihsdisi

// 2. rl_add_history()
// 	library: <readline/history.h>
// 	Input: rl_clear_history(char *)
// 	Output: Nil
// 	Purpose: Used to add the inputs entered bby the users into a struct

// 3. rl_clear_history()
// 	library: <readline/history.h>
// 	Input: rl_clear_history(nil)
// 	Outputs: Nil
// 	Purpose: Clears inputs history that is keyed by user when using readline and stored into rl_add_history.

// 4. rl_on_new_line()
// 	library: <readline/history.h>