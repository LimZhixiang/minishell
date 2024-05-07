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

int	wrd_count(char *new)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	while (new[i])
	{
		if (new[i] != ' ' && ft_quote(new, i) == 0)
		{
			word++;
			while (new[i] && (new[i] != ' ' || ft_quote(new, i) != 0))
				i++;
		}
		else
			i++;
	}
	return (word);
}

int	mini_letters(char *new, int i, int flag)
{
	int	quote;
	int	count;

	count = 0;
	quote = 0;
	while (new[i] && (new[i] != ' ' || quote != 0))
	{
		if ((new[i] == '\'' || new[i] == '\"'))
		{
			if (quote == 0)
				quote = ft_quote_c(new[i]);
			else if (quote == ft_quote_c(new[i]))
				quote = 0;
		}
		count++;
		i++;
	}
	if (flag == 1)
		return (count);
	else
		return (i);
}

void	ft_copy_letters(char *ret, char *new, int i)
{
	int	j;
	int	quote;

	quote = 0;
	j = 0;
	while (new[i] && (new[i] != ' ' || quote != 0))
	{
		if ((new[i] == '\'' || new[i] == '\"'))
		{
			if (quote == 0)
				quote = ft_quote_c(new[i]);
			else if (quote == ft_quote_c(new[i]))
				quote = 0;
		}
		ret[j++] = new[i++];
	}
	ret[j] = '\0';
}

char	*mini_cpy_letters(char *new, int i)
{
	char	*ret;

	ret = malloc(sizeof(char) * mini_letters(new, i, 1) + 1);
	if (!ret)
		return (NULL);
	ft_copy_letters(ret, new, i);
	return (ret);
}

char	**ft_mini_split(char *new)
{
	char	**result;
	int		i;
	int		arg;

	arg = 0;
	i = 0;
	if (wrd_count(new) != 0)
		result = malloc(sizeof(char *) * (wrd_count(new) + 1));
	if (wrd_count(new) == 0 || !result)
		return (NULL);
	while (arg < wrd_count(new))
	{
		while (new[i] == ' ')
			i++;
		result[arg] = mini_cpy_letters(new, i);
		if (result[arg] == NULL)
		{
			free_str_arr(result);
			return (NULL);
		}
		arg++;
		i = mini_letters(new, i, 2);
	}
	result[wrd_count(new)] = NULL;
	return (result);
}
