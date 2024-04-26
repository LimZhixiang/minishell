#include "../../../includes/minishell.h"

int	filehandler(char *filename, int flag)
{
	int	fd;

	fd = 0;
	if (flag == 1)
		fd = open(filename, O_RDONLY);
	else if (flag == 2)
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (flag == 3)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

void	redir(t_mini *mini, t_parse *node)
{
	char	*nxtArg;

	nxtArg = node->next->arg;
	if (node->type == HDOC)
		return ;
	if (node->next->type != FILENAME)
		return;
	if (node->type == INPUT)
		mini->in = filehandler(nxtArg, 1);
	else if (node->type == OUTPUT)
		mini->out = filehandler(nxtArg, 2);
	else if (node->type == APPEND)
		mini->out = filehandler(nxtArg, 3);
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
		node = node->next;
	}
}