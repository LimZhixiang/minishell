/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:55:19 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/08 15:55:22 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str_arr(char **result)
{
	int	i;

	i = 0;
	if (result == NULL)
		return ;
	while (result[i])
		free(result[i++]);
	free(result);
}
