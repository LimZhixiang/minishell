#include "../../../includes/minishell.h"

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