#include "../../../includes/minishell.h"

void	print_file(int fd)
{
	char	*line;
	line = "";
	while (line)
	{
			line = get_next_line(fd);
			if (line)
			{
				printf("%s",line);
				free(line);
			}
	}
}