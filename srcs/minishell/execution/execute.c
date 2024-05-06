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

void	execute(t_mini *mini, t_parse *node, char **envp)
{
	char	*envpath;
	char	*cmdpath;
	char	**cmdarg;

	(void) mini;
	envpath = extract_path(envp);
	cmdarg = get_command(node);
	if (cmdarg == NULL)
	{
		//add freeing of node list
		free(envpath);
		exit(0);
	}
	if (builtin_handler(mini, node, cmdarg))
		exit(mini->status);
	cmdpath = getcmdpath(cmdarg[0], envpath);
	free(envpath);
	if (execve(cmdpath, cmdarg, envp) == -1)
	{
		free(cmdpath);
		free_str_arr(cmdarg);
		// error_checker(3);
	}
}

void	get_execution(t_mini *mini, t_parse *node, char **envp)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (pipe(fds) == -1)
		return ;
	pid = fork();
	// if (pid == -1)
		// error_checker(1);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execute(mini, node, envp);
	}
	else
	{
		close(fds[1]);
		print_file(fds[0]);
		close(fds[0]);
		wait(&status);
	}
	mini->status = WEXITSTATUS(status);
}

void	exec_handler(t_mini *mini, t_parse *node, char **env)
{
	fd_handler(mini, node);
	if (mini->in != -1)
		dup2(mini->in, 0);
	if (mini->out != -1)
		dup2(mini->out, 1);
	get_execution(mini, node, env);
	dup2(mini->term_in, 0);
	dup2(mini->term_out, 1);
	mini->in = -1;
	mini->out = -1;
}
