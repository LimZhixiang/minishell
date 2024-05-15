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

static void	processes(int fds[2], t_parse *node, char **envp, pid_t pid)
{
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], dup(1));
		close(fds[1]);
		execute(node, envp);
	}
	else
	{
		close(fds[1]);
		print_file(fds[0]);
		close(fds[0]);
	}
}

void	execute(t_parse *node, char **envp)
{
	char	*envpath;
	char	*cmdpath;
	char	**cmdarg;

	cmdarg = get_command(node);
	envpath = extract_path(envp);
	cmdpath = NULL;
	if (ft_strchr(cmdarg[0], '/') && cmdarg)
	{
		if (access(cmdarg[0], F_OK | X_OK) == 0)
			execve(cmdarg[0], cmdarg, envp);
		else
			print_cmd_error(cmdarg[0], "");
	}
	else if (cmdarg && envpath)
	{
		cmdpath = getcmdpath(cmdarg[0], envpath);
		execve(cmdpath, cmdarg, envp);
	}
	if (cmdpath)
		free(cmdpath);
	exit(errno);
}

void	get_execution(t_mini *mini, t_parse *node, char **envp)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (pipe(fds) == -1)
	{
		print_cmd_error("pipe", "");
		mini->status = 1;
		return ;
	}
	pid = fork();
	pipe_signal(pid);
	if (pid == 0)
		processes(fds, node, envp, pid);
	else if (pid > 0)
	{
		processes(fds, node, envp, pid);
		wait(&status);
	}
	else
		print_cmd_error("fork", "");
	mini->status = WEXITSTATUS(status);
}

void	exec_handler(t_mini *mini, t_parse *node, char **env)
{
	if (!fd_handler(mini, node))
		return ;
	if (mini->in != -1)
		dup2(mini->in, 0);
	if (mini->out != -1)
		dup2(mini->out, 1);
	if (builtin_handler(mini, node) == 0)
		get_execution(mini, node, env);
	if (mini->in != -1)
		close(mini->in);
	if (mini->out != -1)
		close(mini->out);
	dup2(mini->term_in, 0);
	dup2(mini->term_out, 1);
	mini->in = -1;
	mini->out = -1;
}
