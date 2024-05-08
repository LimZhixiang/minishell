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

int	cmd_word_count(t_parse *input)
{
	t_parse	*temp;
	int		word;

	word = 0;
	temp = input;
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			word++;
		temp = temp->next;
	}
	return (word);
}

char	**get_command(t_parse *input)
{
	char	**ret;
	t_parse	*temp;
	int		i;
	int		count;

	temp = input;
	i = 0;
	count = cmd_word_count(input);
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			ret[i++] = ft_strdup(temp->arg);
		temp = temp->next;
	}
	ret[count] = NULL;
	return (ret);
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
		if (execve(cmdarg[0], cmdarg, envp) == -1)
			print_cmd_error("execve", cmdarg[0]);
	}
	else if (cmdarg && envpath)
	{
		cmdpath = getcmdpath(cmdarg[0], envpath);
		if (execve(cmdpath, cmdarg, envp) == -1)
			print_cmd_error("execve", "");
	}
	if (cmdpath)
		free(cmdpath);
	if (cmdarg)
		free_str_arr(cmdarg);
	if (envpath)
		free(envpath);
}

void	get_execution(t_mini *mini, t_parse *node, char **envp)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (pipe(fds) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execute(node, envp);
	}
	else if(pid > 0)
	{
		close(fds[1]);
		print_file(fds[0]);
		close(fds[0]);
		wait(&status);
	}
	else
		print_cmd_error("pipe", "");
	mini->status = WEXITSTATUS(status);
}

void	exec_handler(t_mini *mini, t_parse *node, char **env)
{
	fd_handler(mini, node);
	if (mini->in != -1)
		dup2(mini->in, 0);
	if (mini->out != -1)
		dup2(mini->out, 1);
	if (builtin_handler(mini, node) == 0)
		get_execution(mini, node, env);
	dup2(mini->term_in, 0);
	dup2(mini->term_out, 1);
	mini->in = -1;
	mini->out = -1;
}
