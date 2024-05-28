/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_find_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:55:19 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/08 15:55:22 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	replace_word(char *line, char *replace)
{
	int	i;

	i = 0;
	while (replace[i])
	{
		*(line + i) = replace[i];
		i++;
	}
	return (i);
}

static int	cpy_words(char *result, char *line, int start, int end)
{
	while (line[start] && start < end)
	{
		*(result + start) = line[start];
		start++;
	}
	return (start);
}

static int	wrd_found(char *line, char *find)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while (line[i])
	{
		while (line[i + end] == find[end] && line[i + end])
			end++;
		if (!find[end])
			return (i);
		end = 0;
		i++;
	}
	return (-1);
}

static void	new_str(char *result, char *line, char *find, char *replace)
{
	int	i;
	int	j;
	int	k;

	j = wrd_found(line, find);
	i = 0;
	i += cpy_words(result, line, 0, j);
	k = i + replace_word(result + i, replace);
	i += ft_strlen(find);
	while (line[i])
		result[k++] = line[i++];
	result[k] = 0;
}

char	*str_find_replace(char *line, char *find, char *replace)
{
	int		i;
	size_t	k;
	char	*result;
	char	*temp;

	result = line;
	i = wrd_found(line, find);
	while (i != -1)
	{
		temp = result;
		k = ft_strlen(result) - ft_strlen(find) + ft_strlen(replace);
		result = malloc(sizeof(char) * (k + 1));
		if (!result)
			return (NULL);
		new_str(result, temp, find, replace);
		if (temp != line)
			free (temp);
		i = wrd_found(result, find);
	}
	return (result);
}
