/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:34:45 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:34:46 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	valid_env_name(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	if (ft_valid_env(line[0]) == 2 || ft_valid_env(line[0]) <= 0)
		return (0);
	while (line[i] && line[i] != '=')
	{
		if (ft_valid_env(line[i] <= 0))
			return (0);
		i++;
	}
	return (1);
}

int	export(t_mini *mini, char **cmdarg)
{
	t_env	*new;
	int		i;

	i = 1;
	while (cmdarg[i])
	{
		if (!ft_strchr(cmdarg[i], '=') || !valid_env_name(cmdarg[i]))
		{
			i++;
			continue ;
		}
		new = create_node(cmdarg[i]);
		add_node(mini->env, new);
		i++;
	}
	return (1);
}

int	unset(t_mini *mini, char **cmdarg)
{
	t_env	*iter;
	t_env	*temp;
	char	*env;
	int		i;

	i = 1;
	iter = mini->env;
	temp = iter;
	while (iter)
	{
		while (cmdarg[i])
		{
			env = get_envp_name(iter->value);
			if (!env)
				return (1);
			if (ft_strcmp(env, cmdarg[i]))
				iter = del_curr_node(temp, iter);
			i++;
			free(env);
		}
		i = 1;
		temp = iter;
			iter = iter->next;
	}
	return (1);
}

