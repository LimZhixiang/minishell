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
		if (ft_valid_env(line[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_current_env(char *arg, t_mini *mini, char *arg_name)
{
	char	*env_name;
	char	*replace;
	t_env	*temp;

	mini->status = 0;
	temp = mini->env;
	while (temp)
	{
		env_name = get_envp_name(temp->value);
		if (ft_strcmp(arg_name, env_name))
		{
			free(temp->value);
			replace = ft_strdup(arg);
			if (replace == NULL)
				print_cmd_error("malloc", "");
			else
				temp->value = replace;
			mini->status = 1;
			free(env_name);
			break ;
		}
		temp = temp->next;
		free(env_name);
	}
	return (mini->status);
}

int	export(t_mini *mini, char **cmdarg)
{
	t_env	*new;
	int		i;
	char	*arg_name;

	mini->status = 0;
	i = 1;
	while (cmdarg[i])
	{
		if (!ft_strchr(cmdarg[i], '=') || !valid_env_name(cmdarg[i]))
		{
			if (!valid_env_name(cmdarg[i]))
				print_env_error(cmdarg[i], mini, 1);
			i++;
			continue ;
		}
		arg_name = get_envp_name(cmdarg[i]);
		if (is_current_env(cmdarg[i], mini, arg_name) == 0)
		{
			new = create_node(cmdarg[i]);
			add_node(mini->env, new);
		}
		free(arg_name);
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
	mini->status = 0;
	while (iter)
	{
		while (cmdarg[i])
		{
			env = get_envp_name(iter->value);
			if (!env)
				return (1);
			if (ft_strcmp(env, cmdarg[i++]))
				iter = del_curr_node(temp, iter);
			free(env);
		}
		i = 1;
		temp = iter;
		iter = iter->next;
	}
	return (1);
}
