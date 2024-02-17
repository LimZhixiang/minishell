#include "minishell.h"

char	*get_envps(char **envp)
{
	int		i;
	int		j;
	int 	k;
	char	*result;

	i = 0;
	k = 0;
	j = 0;
	while (envp[i])
		k += ft_strlen(envp[i++]);
	result = malloc(sizeof(char) *(i + k + 1));
	i = -1;
	k = 0;
	while (envp[++i])
	{
		while(envp[i][j])
			result[k++] = envp[i][j++];
		result[k++] = '\n';
		j = 0;
	}
	result[k] = 0;
	return (result);
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	(void)argc;
	(void)argv;

	line = readline("Minishell: ");
	while (!ft_strcmp(line, ""))
	{
		printf("old line:\t%s\n", line);
		if (ft_strchr(line, '$'))
			line = convert_env(line, envp);
		printf("new line:\t%s\n", line);
		if (find_word(line, "env") != -1)
			printf("%s", get_envps(envp));
		free(line);
		line = readline("Minishell: ");
	}
	free(line);
	return (0);
}
// 1. readline()
// 	library: <readline/readline.h>
// 	Inputs: readline("prompt message")
// 	Outputs: char*

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