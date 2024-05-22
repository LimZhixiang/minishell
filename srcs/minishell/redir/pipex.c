/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zxpipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	subshell_child_fd(t_mini *mini, t_parse *next,
	int input_fd, int *pipefd)
{
	if (mini->status != 0)
		exit(mini->status);
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (mini->in != -1)
	{
		dup2(mini->in, STDIN_FILENO);
		close(mini->in);
	}
	if (next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (mini->out != -1)
	{
		dup2(mini->out, STDOUT_FILENO);
		close(mini->out);
	}
}

static void	subshell_parent(t_pipe info, t_mini *mini)
{
	mini->status = 0;
	if (info.input_fd != -1)
		close(info.input_fd);
	if (info.next != NULL)
	{
		close(info.pipefd[1]);
		*(info.status) = subshell_recus(mini, info.next, info.pipefd[0],
				info.env);
	}
}

static void	subshell_child_process(t_mini *mini, t_pipe info, t_parse *current)
{
	if (mini->status)
		exit(mini->status);
	subshell_child_fd(mini, info.next, info.input_fd, info.pipefd);
	if (info.fd_status)
		execute(current, info.env);
	else
		exit(mini->status);
}

int	subshell_recus(t_mini *mini, t_parse *current, int input_fd, char **env)
{
	int		pipefd[2];
	int		status;
	t_pipe	info;
	pid_t	pid;

	info = subshell_var(nxt_subshell(mini, current), pipefd, env, input_fd);
	if (create_pipe(info.next, pipefd, mini) == 0)
		return (-1);
	info.fd_status = fd_handler(mini, current);
	pid = fork();
	if (pid == 0)
		subshell_child_process(mini, info, current);
	else
	{
		subshell_parent(info, mini);
		waitpid(pid, &status, 0);
		if (info.next == NULL)
		{
			if (WIFSIGNALED(status))
				*(info.status) = get_signal_status(status);
			else
				*(info.status) = WEXITSTATUS(status);
		}
	}
	return (*(info.status));
}
