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

static int	ft_space_line(char *new, char *line)
{
	int	i;
	int	j;
	int	sep;

	sep = 0;
	i = 0;
	j = 0;
	while (new && line[i])
	{
		sep = is_sep(line[i]);
		if (sep != 0 && ft_quote(line, i) == 0)
		{
			if (i != 0 && line[i - 1] != ' ' && is_sep(line[i - 1]) != sep)
				new[j++] = ' ';
			new[j++] = line[i++];
			if (sep != 1 && is_sep(line[i]) == sep)
				new[j++] = line[i++];
			if (!ft_strchr(" \0", line[i]))
				new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	return (1);
}

static char	*malloc_char(int size)
{
	char	*new;

	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	return (new);
}

static char	*ft_alloc_space(char *line)
{
	int		i;
	int		space;
	int		sep;

	space = 0;
	i = 0;
	while (line[i])
	{
		sep = is_sep(line[i]);
		if (sep != 0 && ft_quote(line, i) == 0)
		{
			if (i != 0 && !ft_strchr(" ", line[i - 1])
				&& is_sep(line[i - 1]) != sep)
				space++;
			if (sep != 1 && is_sep(line[i + 1]) == sep)
				i++;
			if (!ft_strchr("\0", line[i + 1]))
				space++;
		}
		i++;
	}
	return (malloc_char(i + space));
}

int	parsing(char *line, t_mini *mini)
{
	char	*space_line;
	char	**split;

	if (check_quote_syntax(line) == 0)
		return (0);
	space_line = ft_alloc_space(line);
	if (space_line == NULL)
		return (0);
	ft_space_line(space_line, line);
	space_line = ft_var_exp(space_line, mini, 1);
	split = ft_mini_split(space_line);
	free(space_line);
	if (split == NULL)
		return (0);
	if (init_input(split, mini) == 0)
		return (0);
	if (check_syntax(mini) == 2)
		return (0);
	ft_rm_quotes(mini);
	return (1);
}
