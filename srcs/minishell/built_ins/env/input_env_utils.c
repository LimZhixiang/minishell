/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	find_env(char *line, char *wrd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (wrd[j] == line[i + j])
		{
			if (wrd[j + 1] == 0)
				if (line[i + j + 1] == ' ' || line[i + j + 1] == 0)
					return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}

char	*get_envp_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
	{
		print_cmd_error("malloc Error", 0, "");
		return (NULL);
	}
	i = 0;
	while (str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
