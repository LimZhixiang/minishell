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

void	heredoc(t_mini *mini, char *eof, int fd)
{
	char	*line;

	while (mini->status == 0)
	{
		line = readline("heredoc> ");
		if (line == 0 || ft_strcmp(line, eof))
		{
			if (line == 0)
				print_cmd_error
					("here-document got end-of-file instead of", eof);
			break ;
		}
		else
		{
			line = ft_var_exp(line, mini);
			ft_putendl_fd(line, fd);
		}
		free(line);
	}
	free(line);
}

void	heredoc_controller(t_mini *mini, char *eof, int fd)
{
	pid_t	pid;
	int		status;

	g_type = 2;
	dup2(mini->term_out, 0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signal);
		heredoc(mini, eof, fd);
		close(fd);
		exit(0);
	}
	else if (pid > 0)
	{
		wait(&status);
		mini->status = WEXITSTATUS(status);
		close(fd);
	}
	else
		print_cmd_error("fork", "");
}
// void	heredoc(t_mini *mini, char *eof)
// {
// 	int		tmpfd;
// 	char	*line;
// 	struct termios old, new;
// 	tcgetattr(0, &old);
// 	new = old;
// 	new.c_lflag &= ~(ICANON | ECHO);
// 	tcsetattr(0, TCSANOW, &new);
// 	(void) mini;
// 	tmpfd = -1;
// 	g_type = 2;
// 	filehandler(".heredoctemp.tmp", &tmpfd, OUTPUT);
// 	while (1)
// 	{
// 		line = readline("heredoc> ");
// 		if (line == 0 || ft_strcmp(line, eof) || *line == 3)
// 		{
// 			if (line == 0)
// 				print_cmd_error
// 					("here-document got end-of-file instead of", eof);
// 			break ;
// 		}
// 		else
// 		{
// 			line = ft_var_exp(line, mini);
// 			ft_putendl_fd(line, tmpfd);
// 		}
// 		free(line);
// 	}
// 	free(line);
// 	close(tmpfd);
// 	tcsetattr(0, TCSANOW, &old);
// }

// void	heredoc(t_mini *mini, char *eof)
// {
// 	int		tmpfd;
// 	char	*line;

// 	(void) mini;
// 	tmpfd = -1;
// 	g_type = 2;
// 	filehandler(".heredoctemp.tmp", &tmpfd, OUTPUT);
// 	while (1)
// 	{
// 		// if (g_type != 3)
// 		// {
// 		line = readline("heredoc> ");
// 		// 	i++;
// 		// 	printf("%s,%i, %i\n", rl_prompt, i, g_type);
// 		// }	
// 		// if (g_type == 3)
// 		// {
// 		// 	break;
// 		// }
// 		if (line == 0 || ft_strcmp(line, eof))
// 		{
// 			if (line == 0)
// 				print_cmd_error
// 					("here-document got end-of-file instead of", eof);
// 			break ;
// 		}
// 		else
// 		{
// 			line = ft_var_exp(line, mini);
// 			ft_putendl_fd(line, tmpfd);
// 		}
// 		free(line);
// 	}
// 	free(line);
// 	close(tmpfd);
// }