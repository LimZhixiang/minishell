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

static void	subshell_parent(t_pipe info, t_mini *mini, pid_t pid)
{
	int	status;

	if (mini->in != -1)
		close(mini->in);
	if (mini->out != -1)
		close(mini->out);
	if (info.input_fd != -1)
		close(info.input_fd);
	if (info.next != NULL)
	{
		close(info.pipefd[1]);
		*info.status = subshell_recus(mini, info.next, info.pipefd[0],
				info.env);
	}
	waitpid(pid, &status, 0);
	if (info.next == NULL)
	{
		if (WIFSIGNALED(status))
			*info.status = get_signal_status(status);
		else
			*info.status = WEXITSTATUS(status);
	}
}

static void	subshell_child_process(t_mini *mini, t_pipe info, t_parse *current)
{
	int	i;

	subshell_child_fd(mini, info.next, info.input_fd, info.pipefd);
	create_error_file(current);
	if (info.fd_status)
	{
		if (!builtin_handler(mini, current))
			execute(mini, current, info.env);
	}
	i = mini->status;
	close(mini->std_err);
	close(mini->term_in);
	close(mini->term_out);
	free_t_parse(mini->input, HDOC);
	free_t_export(mini->list);
	free_t_env(mini->env);
	free_str_arr(info.env);
	free(mini->user_input);
	free(mini);
	exit(i);
}

int	subshell_recus(t_mini *mini, t_parse *current, int input_fd, char **env)
{
	int		pipefd[2];
	t_pipe	info;
	pid_t	pid;
	int		status;

	mini->in = -1;
	mini->out = -1;
	info = subshell_var(nxt_subshell(mini, current), pipefd, env, input_fd);
	info.status = &status;
	if (create_pipe(info.next, pipefd, mini) == 0)
		return (-1);
	info.fd_status = fd_handler(mini, current);
	pid = fork();
	if (pid == 0)
		subshell_child_process(mini, info, current);
	else
		subshell_parent(info, mini, pid);
	return (status);
}
