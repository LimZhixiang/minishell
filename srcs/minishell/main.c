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

int		cmd_word_count(t_parse *input)
{
	t_parse	*temp;
	int		word;

	word = 0;
	temp = input;
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			word++;
		temp = temp->next;
	}
	return (word);
}

char	**get_command(t_parse *input)
{
	char	**ret;
	t_parse *temp;
	int		i;

	temp = input;
	i = 0;
	ret = malloc(sizeof(char *) * (cmd_word_count(input) + 1));
	if (!ret)
		return (NULL);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			ret[i++] = ft_strdup(temp->arg);
		temp = temp->next;
	}
	ret[cmd_word_count(input)] = NULL;
	return(ret);
}

void	minishell(t_mini *mini)
{
	t_parse	*input_cpy;
	char **cmd;

	input_cpy = mini->input;
	while (input_cpy)
	{
		fd_handler(mini, input_cpy);
		cmd = get_command(input_cpy);
		while (input_cpy)
		{
			input_cpy = input_cpy->next;
			if (input_cpy)
				if (input_cpy->type == PIPE)
				{
					input_cpy = input_cpy->next;
					break;
				}
		}
		free(cmd);
	}
	(void) cmd;
}

t_mini	*innit_mini(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	init_mini_env(mini, envp);
	mini->in = -1;
	mini->out = -1;
	mini->term_in = dup(0);
	mini->term_out = dup(1);
	mini->status = 0;
	return(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	(void)argc;
	(void)argv;

	mini = innit_mini(envp);
	while (1)
	{
		signal_controller();
		input = readline("minishell: ");
		if (input_handler(input))
			break;
		parsing(input, mini);
		//fork then call fd_handler maybe ???
		//fd handler gets all fds needed until the pipe node
		free (input);
		minishell(mini);
	}
	free(input);
	return (0);
}

	// 	check_redir(in);
	// 	// will replace arg with cmd when theres no cmd infront of redir
	// 	check_cmd();
	// 	input_cpy = input_cpy->next;
	// 	input_cpy = mini->input;
	// 	get_char**
	// 	change fd
	// 	check_redir();
	// 	cpy_cmd/arg();
	// 	//prioritse | change output to the input
	// 	//execute redir need to make sure the std in change
	// 	//pwd | cat << EOF | cat << EOF
	// 	//pwd | cat << EOF hi bye
	// 	while (input_cpy("|", ">>, <<, <, >"))
	// 	<< eof hi
	// 	echo hi >> | echo he |  ehcih ji
	// }

			// check_for_pipe_redir( |);

		// check_for_pipe_redir(|);
		// check_other_redir(>>);
		// execuve(cmd, mini);
		// while (input_cpy != NULL || input_cpy != '|')
		// {
		// 	input_cpy = input_cpy->next;
		// 	int i = 0;
		// 	while (cmd[i])
		// 	{
		// 		printf("%s\n", cmd[i]);
		// 		i++;
		// 	}	
		// 	free(cmd);
		// }