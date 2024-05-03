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

int	redir_type(t_parse *node, int *type)
{
	int	status;

	status = 1;
	if (ft_strcmp(">", node->arg) == 1)
		*type = OUTPUT;
	else if (ft_strcmp(">>", node->arg) == 1)
		*type = APPEND;
	else if (ft_strcmp("<", node->arg) == 1)
		*type = INPUT;
	else if (ft_strcmp("<<", node->arg) == 1)
		*type = HDOC;
	if (*type >= 6 && *type <= 9)
		status = 0;
	return (status);
}

int	operator_type(t_parse *node, int *CMD_FLAG)
{
	int	type;

	type = ARG;
	if (ft_strcmp("|", node->arg) == 1)
	{
		type = PIPE;
		*CMD_FLAG = 1;
	}
	else if (node->prev != NULL && ft_strcmp("<<", node->prev->arg) == 1)
		type = DELIMITER;
	else if (node->prev != NULL && OUTPUT <= node->prev->type
		&& node->prev->type <= INPUT)
		type = FILENAME;
	else if (*CMD_FLAG == 1 && redir_type(node, &type))
	{
		*CMD_FLAG = 0;
		type = CMD;
	}
	redir_type(node, &type);
	return (type);
}

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

t_parse	*ft_newnode(char *content, t_parse *prev)
{
	t_parse	*new;

	new = malloc(sizeof(t_parse));
	if (!new)
		return (0);
	new->arg = ft_strdup(content);
	new->prev = prev;
	new->next = NULL;
	return (new);
}
