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

int	input_handler(char *input)
{
	if (input == 0)
		return (1);
	if (input && !str_empty(input))
		add_history(input);
	return (0);
}

void	minishell(t_mini *mini)
{
	t_parse	*input_cpy;
	char	**env;

	input_cpy = mini->input;
	env = get_env_arr(mini);
	mini->pipe = pipe_present(mini->input);
	if (heredoc_handler(mini) != 0)
	{
		if (mini->pipe == 1)
			mini->status = subshell_recus(mini, input_cpy, -1, env);
		else
			exec_handler(mini, input_cpy, env);
	}
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
		print_cmd_error("malloc", 0, "");
		exit(1);
	}
	if (!init_mini_env(mini, envp))
		free(mini);
	mini->input = NULL;
	mini->exit = 0;
	mini->in = -1;
	mini->out = -1;
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