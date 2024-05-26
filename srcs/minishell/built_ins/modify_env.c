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
	{
		mini->list = add_export_node(mini->list,
				create_export_node(name, value));
	}
	free(name);
	free(value);
}

static void	export_noarg(t_mini *mini, char *name)
{
	if (!export_exist(mini, name))
		mini->list = add_export_node(mini->list,
				create_export_node(name, NULL));
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
			export_noarg(mini, cmdarg[i]);
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
