/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_mini_out(int fd)
{
	if (fd == -1)
		return (1);
	return (fd);
}

int	echo_handler(t_mini *mini, char **cmdarg)
{
	int	i;
	int	n_flag;
	int	fd;

	fd = check_mini_out(mini->out);
	n_flag = 1;
	i = 1;
	while (cmdarg[i])
	{
		if (i == 1 && ft_strcmp(cmdarg[i], "-n") == 1)
		{
			n_flag = 0;
			i++;
		}
		if (cmdarg[i] != NULL)
		{
			ft_putstr_fd(cmdarg[i], fd);
			if (cmdarg[i + 1] != NULL)
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
	if (n_flag == 1)
		ft_putstr_fd("\n", fd);
	mini->status = 0;
	return (1);
}
