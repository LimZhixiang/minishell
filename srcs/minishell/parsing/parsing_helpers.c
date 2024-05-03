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

int	is_sep(char c)
{
	if (c == '|')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '<')
		return (3);
	return (0);
}

int	ft_quote_c(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	ft_quote(char *line, int i)
{
	int	j;
	int	quote;

	quote = 0;
	j = 0;
	while (line && line[j] && j != i)
	{
		if (quote == 0 && line[j] == '\'')
			quote = 1;
		else if (quote == 0 && line[j] == '\"')
			quote = 2;
		else if (quote == 1 && line[j] == '\'')
			quote = 0;
		else if (quote == 2 && line[j] == '\"')
			quote = 0;
		j++;
	}
	return (quote);
}
