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
				print_cmd_error("malloc Error", 0, "");
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

int	export_handler(t_mini *mini, char **cmdarg)
{
	t_env	*new;
	t_export	export;
	int		i;
	char	*arg_name;

	mini->status = 0;
	i = 1;
	while (cmdarg[i])
	{
		if (!ft_strchr(cmdarg[i], '=') || !valid_env_name(cmdarg[i]))
		{
			print_env_error(cmdarg[i++], mini, 1);
			continue ;
		}
		if (!ft_strchr(cmdarg[i], '='))
		{
			
		}
		arg_name = get_envp_name(cmdarg[i]);
		if (is_current_env(cmdarg[i], mini, arg_name) == 0)
		{
			new = create_node(cmdarg[i]);
			mini->env = add_node(mini->env, new);
		}
		free(arg_name);
		i++;
	}
	return (1);
}

int	export(t_mini *mini, char *env)
{
	t_env	*new;
	char	*arg_name;
	int		status;

	status = 1;
	if (!valid_env_name(env))
	{
		print_env_error(env, mini, 1);
		return (1);
	}
	arg_name = get_envp_name(env);
	if (!arg_name)
		status = 0;
	if (is_current_env(env, mini, arg_name) == 0 && status)
	{
		new = create_node(env);
		mini->env = add_node(mini->env, new);
		if (!new)
			status = 0;
	}
	free(arg_name);
	return (1);
}

int	unset(t_mini *mini, char **cmdarg)
{
	t_env	*iter;
	t_env	*temp;
	int		i;

	i = 1;
	iter = mini->env;
	temp = iter;
	mini->status = 0;
	while (iter)
	{
		while (cmdarg[i])
		{
			if (env_compare(iter->value, cmdarg[i++]))
				iter = del_curr_node(temp, iter, mini);
		}
		i = 1;
		temp = iter;
		if (iter)
			iter = iter->next;
	}
	return (1);
}
