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

void	subshell(t_mini *mini, t_parse *node, char **env)
{
	while (node)
	{
		fd_handler(mini, node);
		pipe_handler(mini, node, env);
		node = node->next;
		while (node)
		{
			if (node->type == PIPE)
			{
				node = node->next;
				break;
			}
			node = node->next;
		}
		mini->pipe = pipe_present(node);
		mini->in = -1;
		mini->out = -1;
		dup2(mini->term_out, 1);
	}
	mini->in = -1;
	mini->out = -1;
	dup2(mini->term_in, 0);
	dup2(mini->term_out, 1);
}

void	minishell(t_mini *mini)
{
	t_parse	*input_cpy;
	char	**env;

	input_cpy = mini->input;
	env = get_env_arr(mini);
	if (mini->pipe == 1)
		subshell(mini, input_cpy, env);
	else
		exec_handler(mini, input_cpy, env);
	if (access(".heredoctemp.tmp", F_OK) == 0)
		unlink(".heredoctemp.tmp");
	free_str_arr(env);
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
	mini->pipe = 0;
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
		free(input);
		mini->pipe = pipe_present(mini->input);
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