#include "../../../includes/minishell.h"


void	filehandler(char *filename, int *fd, int flag)
{
	if (*fd != -1)
	{
		printf("closed %d fd\n", *fd);
		close(*fd);
	}
	if (flag == INPUT)
		*fd = open(filename, O_RDONLY);
	else if (flag == OUTPUT)
		*fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (flag == APPEND)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
	}
	printf("%d fd assigned\n", *fd);
}

void	print_cmd_error(char *cmd, char *str)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ",2);
	if (errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ",2);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	heredoc(t_mini *mini, char *eof)
{
	int		tmpfd;
	char	*line;

	(void) mini;
	tmpfd = -1;
	filehandler(".heredoctemp.tmp", &tmpfd, OUTPUT);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == 0 || ft_strcmp(line, eof))
		{
			if (line == 0)
			{
				print_cmd_error("here-document got EOF signal instead of", eof);
				unlink(".heredoctemp.tmp");
			}
			break ;
		}
		else
			ft_putstr_fd(line, tmpfd);
		free(line);
	}
	free(line);
	close(tmpfd);
}

void	redir(t_mini *mini, t_parse *node)
{
	char	*nxtArg;

	nxtArg = node->next->arg;
	if (node->type == HDOC)
		heredoc(mini, node->next->arg);
	if (node->next->type != FILENAME)
		return;
	if (node->type == INPUT)
		filehandler(nxtArg, &mini->in, INPUT);
	else if (node->type == OUTPUT)
		filehandler(nxtArg, &mini->out, OUTPUT);
	else if (node->type == APPEND)
		filehandler(nxtArg, &mini->out, APPEND);
}

void	fd_handler(t_mini *mini, t_parse *head)
{
	t_parse	*node;
	int		type;

	(void)mini;
	type = 0;
	(void)type;
	node = head;
	while (node != NULL && node->type != PIPE)
	{
		if (node->type >= 6 && node->type <= 9)
			redir(mini, node);
		mini->status = errno;
		if (mini->status == -1)
			break ;
		node = node->next;
	}
}