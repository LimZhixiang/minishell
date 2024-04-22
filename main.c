#include "minishell.h"

int	input_handler(char *input)
{
	if (input == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(1);
	}
	if (input || *input)
		add_history(input);
	if (ft_strcmp(input, "exit"))
		return (1);
	return (0);
}

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
		if (input_handler(input))
			break;
		parsing(input, mini);
		free (input);
	}
	free(input);
	return (0);
}