/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:34:45 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:34:46 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_env(t_mini *mini, char **env)
{
	int	i;
	int	fd;

	fd = mini->out;
	if (fd == -1)
		fd = 1;
	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

int	env_builtin(t_mini *mini, char **cmdarg)
{
	char	**env;

	if (strarr_len(cmdarg) != 1)
		mini->status = 1;
	else
	{
		env = get_env_arr(mini);
		if (env == NULL)
		{
			print_cmd_error("malloc", "");
			mini->status = errno;
		}
		print_env(mini, env);
	}
	return (1);
}
