/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandwich_join.c                       	            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:19:39 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/08 14:19:42 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*sandwich_join(char *bread1, char *jam, char *bread2)
{
	char	*temp;
	char	*result;
	int		status;

	status = 0;
	if (!bread1 || !jam || !bread2)
		return (NULL);
	temp = ft_strjoin(bread1, jam);
	if (!temp)
		status = 1;
	result = ft_strjoin(temp, bread2);
	if (!result)
		status = 1;
	if (status)
		return (NULL);
	free(temp);
	return (result);
}
