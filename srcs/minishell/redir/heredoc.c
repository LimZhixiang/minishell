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

static void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(130);
	}
}

static void	heredoc_signal_controller(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

static void	heredoc(t_mini *mini, char *eof, int fd)
{
	char	*line;

	while (mini->status == 0)
	{
		line = readline("heredoc> ");
		if (line == 0 || ft_strcmp(line, eof))
		{
			if (line == 0)
				print_cmd_error
					("here-document got end-of-file instead of", 0, eof);
			break ;
		}
		else
		{
			line = here_doc_exp(line, mini);
			ft_putendl_fd(line, fd);
		}
		free(line);
	}
	free(line);
}

void	heredoc_controller(t_mini *mini, char *eof, int fd, char *name)
{
	pid_t	pid;
	int		status;

	dup2(mini->term_out, 0);
	pid = fork();
	if (pid == 0)
	{
		heredoc_signal_controller(pid);
		heredoc(mini, eof, fd);
		close(fd);
		free(name);
		free_execution(mini, HDOC);
		exit(0);
	}
	else if (pid > 0)
	{
		heredoc_signal_controller(pid);
		waitpid(pid, &status, 0);
		mini->status = WEXITSTATUS(status);
		close(fd);
	}
	else
		print_cmd_error("fork Error", 0, "");
}
