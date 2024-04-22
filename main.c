#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	(void)argc;
	(void)argv;

	mini = malloc(sizeof(t_mini));
	mini_env(mini, envp);
	while (1)
	{
		signal_controller();
		input = readline("minishell: ");
		if (input == 0)
		{
			ft_putstr_fd("exit\n", 2);
			exit(1);
		}
		if (input || *input)
			add_history(input);
		parsing(input, mini);
		if (ft_strcmp(input, "exit"))
			break ;
		free (input);
	}
	free(input);
	return (0);
}