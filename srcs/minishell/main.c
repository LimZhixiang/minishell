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
	mini->status = 0;
	while (input_cpy != NULL)
	{
		cmd = get_command(input_cpy);
		check_for_pipe_redir( |);
		check_other_redir(>>);
		execuve(cmd, mini);
		while (input_cpy != NULL || input_cpy != '|')
		{
			input_cpy = input_cpy->next;
			int i = 0;
			while (cmd[i])
			{
				printf("%s\n", cmd[i]);
				i++;
			}	
			free(cmd)
		}
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
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	(void)argc;
	(void)argv;

	mini = malloc(sizeof(t_mini));
	mini_env(mini, envp);
	mini->in = dup(0);
	mini->out = dup(1);
	while (1)
	{
		signal_controller();
		input = readline("minishell: ");
		if (input_handler(input))
			break;
		syntax_check();
		parsing(input, mini);
		minishell(mini);
		free (input);
	}
	free(input);
	return (0);
}