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

static int	valid_env_name(char *line)
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

int	is_current_env(t_mini *mini, char *arg, char *arg_name)
{
	char	*replace;
	t_env	*temp;
	int		status;

	status = 0;
	temp = mini->env;
	while (temp)
	{
		if (env_compare(temp->value, arg_name))
		{
			free(temp->value);
			replace = ft_strdup(arg);
			if (replace == NULL)
				print_cmd_error("malloc Error", 0, "");
			else
			{
				rplace_export_value(mini, arg, arg_name);
				temp->value = replace;
			}
			status = 1;
			break ;
		}
		temp = temp->next;
	}
	return (status);
}

void	new_env_var(t_mini *mini, char *env)
{
	char	*name;
	char	*value;

	name = get_envp_name(env);
	value = get_envp_value(env);
	if (!name | !value)
		return ;
	export(mini, env);
	if (export_exist(mini, name))
		rplace_export_value(mini, env, name);
	else
		mini->list = add_export_node(mini->list, create_export_node(name, value));
	free(name);
	free(value);
}

int	export_handler(t_mini *mini, char **cmdarg)
{
	int		i;
	char	*arg_name;

	mini->status = 0;
	i = 1;
	if (!cmdarg[1])
		print_export_lst(mini);
	while (cmdarg[i])
	{
		if (!valid_env_name(cmdarg[i]))
			print_env_error(cmdarg[i], mini, 1);
		else if (!ft_strchr(cmdarg[i], '='))
		{
			if (!export_exist(mini, cmdarg[i]))
				mini->list = add_export_node(mini->list, create_export_node(cmdarg[i], NULL));
		}
		else
		{
			arg_name = get_envp_name(cmdarg[i]);
			if (is_current_env(mini, cmdarg[i], arg_name) == 0)
				new_env_var(mini, cmdarg[i]);
			free(arg_name);
		}
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
	if (is_current_env(mini, env, arg_name) == 0 && status)
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
	if (!cmdarg[i])
		return (1);
	while (iter && cmdarg[i])
	{
		while (cmdarg[i])
		{
			if (env_compare(iter->value, cmdarg[i]))
				iter = del_curr_node(temp, iter, mini);
			if (export_exist(mini, cmdarg[i]))
				mini->list = rmv_list(mini->list, cmdarg[i]);
			i++;
		}
		i = 1;
		temp = iter;
		if (iter)
			iter = iter->next;
	}
	return (1);
}
