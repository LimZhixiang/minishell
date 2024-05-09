/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:51:34 by yraynen           #+#    #+#             */
/*   Updated: 2023/10/12 17:06:22 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_check(int (func(int)), char *str)
{
	int	i;
	int	status;

	i = 0;
	status = 1;
	if (!str)
		return (0);
	while (str[i] && status)
	{
		status = func(str[i]);
		i++;
	}
	return (status);
}