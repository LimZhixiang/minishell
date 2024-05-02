#include "../../../includes/minishell.h"

void	filehandler(char *filename, int *fd, int flag)
{
	if (*fd != -1)
	{
		// printf("closed %d fd\n", *fd);
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
	// printf("%d fd assigned\n", *fd);
}

void	redir(t_mini *mini, t_parse *node)
{
	char	*nxtArg;

	nxtArg = node->next->arg;
	if (node->type == HDOC)
	{
		heredoc(mini, node->next->arg);
		filehandler(".heredoctemp.tmp", &mini->in, INPUT);
	}
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