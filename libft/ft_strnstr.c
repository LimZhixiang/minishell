/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:59:52 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/08 15:59:54 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*sub == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		if (str[i] == sub[j])
		{
			while (str[i + j] == sub[j] && i + j < len)
			{
				if (sub[j + 1] == 0)
					return ((char *)str + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
