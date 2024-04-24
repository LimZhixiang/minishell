#include "../../includes/minishell.h"

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

void	minishell(t_mini *mini)
{
	t_parse	*input_cpy;

	input_cpy = mini->input;
	mini->in = dup(0);
	mini->out = dup(1);
	mini->status = 0;
	while (input_cpy != NULL)
	{
		//prioritse | change output to the input
		//execute redir need to make sure the std in change
		//pwd | cat << EOF | cat << EOF
		//pwd | cat << EOF hi bye
		while (input_cpy("|", ">>, <<, <, >"))
	}
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
		minishell(mini);
		free (input);
	}
	free(input);
	return (0);
}