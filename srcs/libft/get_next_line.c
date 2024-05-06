/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:51:34 by yraynen           #+#    #+#             */
/*   Updated: 2023/10/12 17:06:22 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*nextline(char *line)
{
	int		i;
	int		j;
	char	*nxt;

	i = 0;
	j = 0;
	nxt = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (0);
	nxt = malloc(sizeof(char) * (ft_strlen(line) - i));
	if (!nxt)
		return (0);
	i++;
	while (line[i + j])
	{
		nxt[j] = line[i + j];
		j++;
	}
	nxt[j] = 0;
	line[i] = 0;
	return (nxt);
}

void	errorchecker(char *lbuffer, char *origin)
{
	if (origin != lbuffer)
	{
		free(origin);
		free(lbuffer);
		return ;
	}
	free(lbuffer);
}

char	*readfile(int fd, char *buffer, char *lbuffer)
{
	ssize_t	byteread;
	char	*origin;
	char	*temp;

	if (!lbuffer)
		lbuffer = ft_strdup("");
	origin = lbuffer;
	byteread = 1;
	while (byteread && !ft_strchr(lbuffer, '\n'))
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread <= 0)
		{
			if (byteread == 0)
				break ;
			errorchecker(lbuffer, origin);
			return (0);
		}
		buffer[byteread] = 0;
		temp = lbuffer;
		lbuffer = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (lbuffer);
}

char	*get_next_line(int fd)
{
	static char	*lbuffer;
	char		*line;
	char		*buffer;

	if (BUFFER_SIZE > (size_t) - 1 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = readfile(fd, buffer, lbuffer);
	free(buffer);
	if (!line)
	{
		lbuffer = 0;
		return (0);
	}
	lbuffer = nextline(line);
	if (!lbuffer && !line[0])
	{
		free(line);
		return (0);
	}
	return (line);
}
