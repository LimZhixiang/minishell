/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	redir_type(t_parse *node, int *type)
{
	int	status;

	status = 1;
	if (ft_strcmp(">", node->arg) == 1)
		*type = OUTPUT;
	else if (ft_strcmp(">>", node->arg) == 1)
		*type = APPEND;
	else if (ft_strcmp("<", node->arg) == 1)
		*type = INPUT;
	else if (ft_strcmp("<<", node->arg) == 1)
		*type = HDOC;
	if (*type >= 6 && *type <= 9)
		status = 0;
	return (status);
}

int	tokenization(t_parse *node, int *CMD_FLAG)
{
	int	type;

	type = ARG;
	if (ft_strcmp("|", node->arg) == 1)
	{
		type = PIPE;
		*CMD_FLAG = 1;
	}
	else if (node->prev != NULL && ft_strcmp("<<", node->prev->arg) == 1)
		type = DELIMITER;
	else if (node->prev != NULL && OUTPUT <= node->prev->type
		&& node->prev->type <= INPUT)
		type = FILENAME;
	else if (*CMD_FLAG == 1 && redir_type(node, &type))
	{
		*CMD_FLAG = 0;
		type = CMD;
	}
	redir_type(node, &type);
	return (type);
}
