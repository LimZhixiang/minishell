#include "../../../includes/minishell.h"

static void print_env(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (mini->out != -1)
		{
			ft_putstr_fd(env[i], mini->out);
			ft_putstr_fd("\n", mini->out);
		}
		else
		{
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}

int	env_builtin(t_mini *mini, char **cmdarg)
{
	char	**env;

	if (strarr_len(cmdarg) != 1)
	{
		mini->status = 1;
		return (1);
	}
	env = get_env_arr(mini);
	if (env == NULL)
	{
		print_cmd_error("malloc", "");
		return (1);
	}
	print_env(mini, env);
	return (1);
}