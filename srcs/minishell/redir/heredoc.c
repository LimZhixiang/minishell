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

char	*get_line_env_heredoc(char *line, t_mini *mini, int i, int j)
{
	char	*env_name;
	char	*env_result;

	env_name = ft_substr(line, i, j);
	if (env_name == NULL)
		return (NULL);
	env_result = ft_get_env(env_name, mini);
	line = replace_env(line, env_result, env_name, i);
	free(env_name);
	if (env_result != NULL)
		free(env_result);
	return (line);
}

char	*here_doc_exp(char *arg, t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && ft_valid_env(arg[i + 1]) != 0)
		{
			j = 1;
			while (ft_valid_env(arg[i + j]) > 0)
				j++;
			if (ft_valid_env(arg[i + j]) == -1 && j == 1)
				arg = get_status_code(arg, mini, i);
			else
				arg = get_line_env_heredoc(arg, mini, i, j);
			if (arg == NULL)
				return (NULL);
			i = -1;
		}
		i++;
	}
	return (arg);
}

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

void	heredoc_controller(t_mini *mini, char *eof, int fd)
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
		exit(0);
	}
	else if (pid > 0)
	{
		heredoc_signal_controller(pid);
		wait(&status);
		mini->status = WEXITSTATUS(status);
		close(fd);
	}
	else
		print_cmd_error("fork Error", 0, "");
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