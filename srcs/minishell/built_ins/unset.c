/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:34:45 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:34:46 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	unset(t_mini *mini, char **cmdarg)
{
	t_env	*iter;
	t_env	*temp;
	int		i;

	i = 1;
	iter = mini->env;
	temp = iter;
	mini->status = 0;
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
