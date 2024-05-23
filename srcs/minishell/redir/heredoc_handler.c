/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zx_fd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	here_doc(t_mini *mini, t_parse *node, char *name)
{
	int		herefd;

	herefd = -1;
	node->heredoc = ft_strdup(name);
	mini->status = filehandler(name, &herefd, OUTPUT);
	heredoc_controller(mini, node->next->arg, herefd);
	close(herefd);
	if (mini->status == 0)
		mini->status = filehandler(name, &mini->in, INPUT);
	if (mini->status)
		return (0);
	else
		return (1);
}

static char	*heredoc_name(int i)
{
	char	*no;
	char	*ret;

	no = ft_itoa(i);
	ret = ft_strjoin(no, "heredoc.tmp");
	free (no);
	return (ret);
}

int	heredoc_handler(t_mini *mini)
{
	t_parse	*node;
	int		i;
	char	*name;

	i = 1;
	node = mini->input;
	while (node != NULL && i != 0)
	{
		name = heredoc_name(i);
		while (node && node->type != PIPE)
		{
			if (node->type == HDOC)
				if (!name || !here_doc(mini, node, name))
					i = 0;
			node = node->next;
		}
		free(name);
		if (!node)
			break ;
		node = node->next;
	}
	return (i);
}
