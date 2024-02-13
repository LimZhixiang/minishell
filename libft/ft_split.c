/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 06:28:10 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/10 06:28:12 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwrd(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

static char	**freesplit(char **result, size_t i)
{
	while (i--)
		free(result[i]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t				i;
	char const			*start;
	char				**result;

	i = 0;
	result = malloc((countwrd(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s != c && *s)
				s++;
			result[i++] = ft_substr(start, 0, s - start);
			if (!result[i - 1])
				return (freesplit(result, i));
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
