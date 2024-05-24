/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_file(int fd)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			write(2, line, ft_strlen(line));
			free(line);
		}
	}
	close(fd);
}

char	*get_filename(int i)
{
	char	*ret;
	char	*full;
	char	*no;

	no = ft_itoa(i);
	if (!no)
		return (NULL);
	ret = ft_strjoin(no, "error.tmp");
	free(no);
	if (!ret)
		return (NULL);
	full = ft_strjoin("./redir", ret);
	free(ret);
	if (!full)
		return (NULL);
	return (full);
}

void	print_error_file(t_mini *mini)
{
	int		i;
	t_parse	*tmp;
	int		fd;
	char	*filename;

	tmp = mini->input;
	i = 1;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->prev == NULL)
		{
			if (tmp->type == PIPE)
				i++;
			filename = get_filename(i);
			filehandler(filename, &fd, INPUT);
			if (access(filename, F_OK) == 0)
				unlink(filename);
			free(filename);
			print_file(fd);
		}
		tmp = tmp->next;
	}
}

void	create_error_file(t_parse *current)
{
	t_parse	*node;
	int		i;
	int		fd;
	char	*name;

	node = current;
	i = 1;
	while (node != NULL)
	{
		if (node->type == PIPE)
			i++;
		node = node->prev;
	}
	name = get_filename(i);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	{
		free(name);
		dup2(fd, STDERR_FILENO);
		close(fd);
	}
}
