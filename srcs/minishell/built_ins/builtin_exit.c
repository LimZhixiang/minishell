/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:09:11 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/09 18:10:40 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exit_str_check(int (func(int)), char *str)
{
	int	i;
	int	status;

	i = 0;
	status = 1;
	if (!str)
		return (0);
	while (str[i] == '-' || str[i] == '+')
	{
		if (i++ != 0)
			return (0);
	}
	while (str[i] && status)
	{
		status = func(str[i]);
		i++;
	}
	return (status);
}

int	get_exit_status(char *cmdarg)
{
	int	ret;

	if (cmdarg[0] != '-')
		return (ft_atoi(cmdarg));
	else
	{
		ret = ft_atoi(cmdarg + 1);
		ret = ~ret;
		ret = ret + 1;
	}
	return (ret);
}

int	mini_exit(t_mini *mini, char **cmdarg)
{
	if (strarr_len(cmdarg) > 2)
	{
		mini->status = 1;
		print_cmd_error("exit", 0, "too many arguments");
	}
	else if (strarr_len(cmdarg) <= 2)
	{
		if (strarr_len(cmdarg) == 1)
			mini->status = 0;
		else if (exit_str_check(&ft_isdigit, cmdarg[1]))
			mini->status = get_exit_status(cmdarg[1]);
		else
		{
			mini->status = 2;
			print_cmd_error("exit", 0, "numeric argument required");
		}
		mini->exit = 1;
	}
	return (1);
}
