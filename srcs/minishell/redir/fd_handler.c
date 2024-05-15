/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	filehandler(char *filename, int *fd, int flag)
{
	if (*fd != -1)
		close(*fd);
	if (flag == INPUT)
		*fd = open(filename, O_RDONLY);
	else if (flag == OUTPUT)
		*fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (flag == APPEND)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		print_cmd_error("", filename);
	return (errno);
}

int	redir(t_mini *mini, t_parse *node)
{
	char	*nxtarg;
	int		herefd;

	herefd = -1;
	nxtarg = node->next->arg;
	if (node->type == HDOC)
	{
		mini->status = filehandler(".heredoctemp.tmp", &herefd, OUTPUT);
		heredoc_controller(mini, node->next->arg, herefd);
		if (mini->status == 0)
			mini->status = filehandler(".heredoctemp.tmp", &mini->in, INPUT);
	}
	else if (node->type == INPUT)
		mini->status = filehandler(nxtarg, &mini->in, INPUT);
	else if (node->type == OUTPUT)
		mini->status = filehandler(nxtarg, &mini->out, OUTPUT);
	else if (node->type == APPEND)
		mini->status = filehandler(nxtarg, &mini->out, APPEND);
	// if (herefd != -1)
	// 	close(herefd);
	if (mini->status)
		return (0);
	else
		return (1);
}

int	fd_handler(t_mini *mini, t_parse *head)
{
	t_parse	*node;

	node = head;
	while (node != NULL && node->type != PIPE)
	{
		if (node->type >= 6 && node->type <= 9)
			if (!redir(mini, node))
				break ;
		node = node->next;
	}
	if (node != NULL && node->type != PIPE)
		return (0);
	else
		return (1);
}
