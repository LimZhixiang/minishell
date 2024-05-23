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

int	export_exist(t_mini *mini, char *name)
{
	t_export	*iter;

	iter = mini->list;
	while (iter)
	{
		if (ft_strcmp(iter->name, name))
			return (1);
		iter = iter->next;
	}
	return (0);
}

t_export	*rmv_list(t_export *list, char *name)
{
	t_export	*iter;
	t_export	*temp;

	temp = list;
	iter = list;
	while (iter)
	{
		if (ft_strcmp(iter->name, name))
		{
			temp = del_export_node(temp, iter);
			break ;
		}
		temp = iter;
		if (iter)
			iter = iter->next;
	}
	return(list);
}

void	rplace_export_value(t_mini *mini, char *arg, char *arg_name)
{
	t_export	*iter;
	iter = mini->list;
	while (iter)
	{
		if (ft_strcmp(iter->name, arg_name))
		{
			free(iter->value);
			iter->value = get_envp_value(arg);
			break ;
		}
		iter = iter->next;
	}
}

void	print_export_lst(t_mini *mini)
{
	t_export	*iter;

	iter = mini->list;
	while(iter)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(iter->name, 1);
		if (iter->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(iter->value, 1);
			ft_putstr_fd("\"",1);
		}
		ft_putchar_fd('\n', 1);
		iter = iter->next;
	}
}

void	export_list(t_mini *mini, char *env)
{
	t_export 	*result;
	char		*value;

	if (ft_strchr(env, '='))
	{
		result = create_export_node(env, NULL);
		if (!result)
			return ;
		mini->list = add_export_node(mini->list, result);
	}
	else
	{
		value = get_envp_value(env);
		result = create_export_node(env, value);
		if (!result)
			return ;
		mini->list = add_export_node(mini->list, result);
		free(value);
	}
	free(result);
}