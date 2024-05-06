#include "../../../includes/minishell.h"

int	builtin_handler(t_mini *mini, t_parse *node)
{
	(void) mini;
	int		status;
	char	**cmdarg;

	status = 0;
	cmdarg = get_command(node);
	if(cmdarg == NULL)
		return (0);
	if (ft_strcmp(cmdarg[0], "cd"))
		status = cd_handler(mini, cmdarg);
	else if (ft_strcmp(cmdarg[0], "pwd"))
		status = pwd_handler(mini);
	// else if (ft_strcmp(cmdarg[0], "export"))
	// 	;
	// else if (ft_strcmp(cmdarg[0], "unset"))
	// 	;
	else if (ft_strcmp(cmdarg[0], "env"))
		status = env_builtin(mini, cmdarg);
	else if (ft_strcmp(cmdarg[0], "exit"))
		status = 1;
	free_str_arr(cmdarg);
	return (status);
}