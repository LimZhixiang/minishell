/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_type;

int	input_handler(char *input)
{
	if (input == 0)
		return (1);
	if (input || *input)
		add_history(input);
	return (0);
}

void	subshell(t_mini *mini, t_parse *node, char **env)
{
	while (node)
	{
		if (fd_handler(mini, node))
		{
			if (mini->in != -1)
				dup2(mini->in, 0);
			if (mini->out != -1)
				dup2(mini->out, 1);
			pipe_handler(mini, node, env);
		}
		node = nxt_subshell(mini, node);
	}
	if (mini->in != -1)
		close(mini->in);
	if (mini->out != -1)
		close(mini->out);
}

void	minishell(t_mini *mini)
{
	t_parse	*input_cpy;
	char	**env;

	input_cpy = mini->input;
	env = get_env_arr(mini);
	mini->pipe = pipe_present(mini->input);
	if (mini->pipe == 1)
		subshell(mini, input_cpy, env);
	else
		exec_handler(mini, input_cpy, env);
	if (access(".heredoctemp.tmp", F_OK) == 0)
		unlink(".heredoctemp.tmp");
	mini->in = -1;
	mini->out = -1;
	dup2(mini->term_in, 0);
	dup2(mini->term_out, 1);
	free_str_arr(env);
}

t_mini	*innit_mini(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void) argc;
	(void) argv;
	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		print_cmd_error("malloc", "");
		exit(errno);
	}
	if (init_mini_env(mini, envp))
		free(mini);
	mini->input = NULL;
	mini->exit = 0;
	mini->in = -1;
	mini->out = -1;
	// int	i;
	// i = 0;
	// struct termios term;
	// while (i <= 9484)
	// {
	// 	if (isatty(i))
	// 	{
	// 		printf("%s\n", ttyname(i));
	// 		printf("%d connected\n", i);

	// 		tcgetattr(i, &term);
	// 	}
	// 	i++;
	// }
	mini->term_in = dup(0);
	mini->term_out = dup(1);
	mini->pipe = 0;
	mini->status = 0;
	return (mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		status;

	mini = innit_mini(argc, argv, envp);
	while (mini->exit == 0)
	{
		signal_controller();
		mini->user_input = readline("minishell: ");
		if (input_handler(mini->user_input))
			break ;
		if (parsing(mini->user_input, mini) == 0)
		{
			ft_free_all(mini, RE_SHELL);
			continue ;
		}
		minishell(mini);
		ft_free_all(mini, RE_SHELL);
	}
	status = mini->status;
	ft_free_all(mini, EXIT_SHELL);
	rl_clear_history();
	ft_putstr_fd("exit\n", 2);
	return (status);
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