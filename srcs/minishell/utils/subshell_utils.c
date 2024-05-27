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

int	create_pipe(t_parse *next, int *pipefd, t_mini *mini)
{
	if (next != NULL)
	{
		if (pipe(pipefd) == -1)
		{
			mini->status = 1;
			return (0);
		}
		return (1);
	}
	return (1);
}

t_pipe	subshell_var(t_parse *next, int *pipe, char **envs, int fd_input)
{
	t_pipe	ret;

	ret.env = envs;
	ret.next = next;
	ret.pipefd = pipe;
	ret.input_fd = fd_input;
	ret.status = NULL;
	return (ret);
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
