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
		{
			if (execve(cmdarg[0], cmdarg, envp) == -1)
			{
				print_cmd_error("execve error", 0, "");
				exit(1);
			}
		}
		else
			print_cmd_error(cmdarg[0], 0, "");
	}
	else if (cmdarg && envpath)
	{
		cmdpath = getcmdpath(cmdarg[0], envpath);
		if (execve(cmdpath, cmdarg, envp) == -1)
		{
			print_cmd_error("execve error", 0, "");
			exit(1);
		}
	}
	if (cmdpath)
		free(cmdpath);
}

void	get_execution(t_mini *mini, t_parse *node, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	pipe_signal(pid);
	if (pid == 0)
		execute(node, envp);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		print_cmd_error("fork Error", 0, "");
	if (WIFSIGNALED(status))
		mini->status = get_signal_status(status);
	else
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
}
