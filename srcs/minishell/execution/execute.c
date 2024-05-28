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

static int	exec_path_check(char *path)
{
	int	status;

	status = 0;
	if (access(path, F_OK) == 0)
	{
		if (access(path, F_OK | X_OK) == -1)
		{
			print_cmd_error(path, EACCES, "");
			status = 126;
		}
		else if (is_direct(path) == 1)
		{
			print_cmd_error(path, EISDIR, "");
			status = 126;
		}
	}
	else
	{
		print_cmd_error(path, ENOENT, "");
		status = 127;
	}
	return (status);
}

void	free_exec_var(char **cmdarg, char *cmdpath, char**envp)
{
	free(cmdpath);
	free_str_arr(cmdarg);
	free_str_arr(envp);
}

void	execute(t_mini *mini, t_parse *node, char **envp)
{
	char	*envpath;
	char	*cmdpath;
	char	**cmdarg;
	int		status;

	cmdarg = get_command(node);
	cmdpath = NULL;
	status = 0;
	free_execution(mini, 0);
	if (cmdarg[0] != NULL && ft_strchr(cmdarg[0], '/') && cmdarg)
	{
		status = exec_path_check(cmdarg[0]);
		if (status == 0)
			execve(cmdarg[0], cmdarg, envp);
	}
	else if (cmdarg[0])
	{
		envpath = extract_path(envp);
		cmdpath = getcmdpath(cmdarg[0], envpath, &status);
		if (cmdpath)
			execve(cmdpath, cmdarg, envp);
	}
	free_exec_var(cmdarg, cmdpath, envp);
	exit(status);
}

static void	get_execution(t_mini *mini, t_parse *node, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	pipe_signal(pid);
	if (pid == 0)
		execute(mini, node, envp);
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
