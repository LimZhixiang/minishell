#include "../../../includes/minishell.h"

int	str_check(int (func(int)), char *str)
{
	int	i;
	int	status;

	i = 0;
	status = 1;
	if (!str)
		return (0);
	while (str[i] && status)
	{
		status = func(str[i]);
		i++;
	}
	return (status);
}

int	mini_exit(t_mini *mini, char **cmdarg)
{
	if (strarr_len(cmdarg) > 2)
	{
		mini->status = 1;
		print_cmd_error("exit", "too many arguments");
	}
	else if (strarr_len(cmdarg) == 2)
	{
		if (str_check(&ft_isdigit, cmdarg[1]))
			mini->status = atoi(cmdarg[1]);
		else
		{
			mini->status = 2;
			print_cmd_error("exit", "numeric argument required");
		}
		mini->exit = 1;
	}
	return (1);
}