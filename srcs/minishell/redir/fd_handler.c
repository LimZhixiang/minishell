#include "../../../includes/minishell.h"

// int	filehandler(char *filename, int flag)
// {
// 	int	fd;

// 	fd = 0;
// 	if (flag == 1)
// 		fd = open(filename, O_RDONLY);
// 	else if (flag == 2)
// 		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	else if (flag == 3)
// 		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		putstr_fd(2, strerror(errno));
// 		putstr_fd(2, ": ");
// 		putstr_fd(2, filename);
// 		putstr_fd(2, "\n");
// 		exit(0);
// 	}
// 	return (fd);
// }


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
		node = node->next;
	}
}