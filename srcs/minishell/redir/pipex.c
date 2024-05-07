/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pipex(t_mini *mini, t_parse *node, char **envp)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (pipe(fds) == -1)
		return ;
	pid = fork();
	// if (pid == -1)
	// 	error_checker(1);
	if (pid == 0)
	{
		if (mini->out == -1)
			dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		if (builtin_handler(mini, node))
			exit(mini->status);
		execute(node, envp);
	}
	else
	{
		dup2(fds[0], 0);
		close(fds[1]);
		if (mini->pipe == 0)
		{
			if (mini->out != -1)
				dup2(fds[0], mini->out);
			else
				dup2(mini->term_out, 1);
			print_file(fds[0]);
		}
		close(fds[0]);
		wait(&status);
	}
	mini->status = WEXITSTATUS(status);
}

void	pipe_handler(t_mini *mini, t_parse *node, char **envp)
{
	if (mini->in != -1)
		dup2(mini->in, 0);
	if (mini->out != -1)
		dup2(mini->out, 1);
	pipex(mini, node, envp);
}
