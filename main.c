#include "minishell.h"

void	print_env(t_mini *mini)
{
	while (mini->env)
	{
		printf("%s\n", mini->env->value);
		mini->env = mini->env->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	int		exit = 0;
	(void)argc;
	(void)argv;

	mini = malloc(sizeof(t_mini));
	mini_env(mini, envp);
	while (exit == 0)
	{
		input = readline("minishell: ");
		parsing(input, mini);
		free (input);
	}
	return (0);
}