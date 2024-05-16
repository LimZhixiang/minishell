/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*     pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	processes(int fds[2], t_parse *node, char **envp, t_mini *mini)
{
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	if (builtin_handler(mini, node))
		exit(mini->status);
	execute(node, envp);
}

static int	pipex(t_mini *mini, t_parse *node, char **envp, int fds[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	pipe_signal(pid);
	if (pid == 0)
		processes(fds, node, envp, mini);
	else if (pid > 0)
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
		waitpid(pid, &status, 0);
	}
	else
		print_cmd_error("fork", "");
	return (status);
}

void	pipe_handler(t_mini *mini, t_parse *node, char **envp)
{
	int		fds[2];
	int		status;

	if (pipe(fds) == -1)
	{
		print_cmd_error("pipe", "");
		mini->status = errno;
		return ;
	}
	status = pipex(mini, node, envp, fds);
	if (WIFSIGNALED(status))
		mini->status = get_signal_status(status);
	else
		mini->status = WEXITSTATUS(status);
}

//cat <"./test_files/infile" | echo hi
//suppose to print hi but didnt print
//echo <missing <"./test_files/infile" <missing
//suppose to print only one missing hi