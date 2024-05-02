#include "../../../includes/minishell.h"

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
				print_cmd_error("here-document got end-of-file instead of", eof);
			break ;
		}
		else
			ft_putendl_fd(line, tmpfd);
		free(line);
	}
	free(line);
	close(tmpfd);
}