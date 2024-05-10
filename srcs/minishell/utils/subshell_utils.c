/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	pipe_present(t_parse *head)
{
	t_parse	*node;

	node = head;
	while (node)
	{
		if (node->type == PIPE)
			return (1);
		node = node->next;
	}
	return (0);
}

t_parse	*nxt_subshell(t_mini *mini, t_parse *node)
{
	t_parse	*nxt;

	nxt = node->next;
	while (nxt)
	{
		if (nxt->type == PIPE)
		{
			nxt = nxt->next;
			break ;
		}
		nxt = nxt->next;
	}
	mini->pipe = pipe_present(nxt);
	mini->in = -1;
	mini->out = -1;
	return (nxt);
}
