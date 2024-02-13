/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:09:11 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/09 18:10:40 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dest);
	s = ft_strlen(src);
	i = 0;
	if (!destsize || d >= destsize)
		return (s + destsize);
	while (src[i] && i < destsize - d - 1)
	{
		dest[i + d] = src[i];
		i++;
	}
	dest[d + i] = 0;
	return (s + d);
}
