/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_direct(char *path)
{
	DIR	*direct;

	direct = opendir(path);
	if (direct == NULL)
		return (0);
	closedir(direct);
	return (1);
}
