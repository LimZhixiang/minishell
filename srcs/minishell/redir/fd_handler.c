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

int	error_file_handler(char *filename, int flag)
{
	int	status;

	status = 0;
	if (access(filename, F_OK) == -1)
	{
		print_cmd_error("", ENOENT, filename);
		status = 127;
	}
	else if (access(filename, F_OK & R_OK) == -1 && flag == INPUT)
	{
		print_cmd_error("", EACCES, filename);
		status = 1;
	}
	else if (access(filename, F_OK & R_OK & W_OK) == -1 && flag == OUTPUT)
	{
		print_cmd_error("", EACCES, filename);
		status = 1;
	}
	return (status);
}

int	filehandler(char *filename, int *fd, int flag)
{
	int	status;

	status = 0;
	if (*fd != -1)
		close(*fd);
	if (flag == INPUT)
		*fd = open(filename, O_RDONLY);
	else if (flag == OUTPUT)
		*fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (flag == APPEND)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		status = error_file_handler(filename, flag);
	return (status);
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
