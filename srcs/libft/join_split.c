/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxlim   <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:11:15 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/06 16:13:34 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_split(char **split, char *env_result)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (split[i])
		j = j + ft_strlen(split[i++]);
	new = malloc(sizeof(char) * (j + (i - 1) + 1));
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
			new[k++] = split[i][j++];
		if (split[i + 1])
			new[k++] = ' ';
		i++;
	}
	new[k] = '\0';
	free(env_result);
	return (new);
}
