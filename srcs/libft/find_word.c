/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:55:19 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/08 15:55:22 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_word(char *line, char *wrd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ' || i == 0)
		{
			while (wrd[j] == line[i + j])
			{
				if (wrd[j + 1] == 0)
					if (line[i + j + 1] == ' ' || line[i + j + 1] == 0)
						return (i);
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (-1);
}
