#include "minishell.h"

int main()
{
	char *line;
	line = NULL;
	line = readline("Minishell: ");
	printf("%s", line);
	return 0;
}
