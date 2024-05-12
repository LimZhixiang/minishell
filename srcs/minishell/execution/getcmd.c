/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*     pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

static int	cmd_word_count(t_parse *input)
{
	t_parse	*temp;
	int		word;

	word = 0;
	temp = input;
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			word++;
		temp = temp->next;
	}
	return (word);
}

char	**get_command(t_parse *input)
{
	char	**ret;
	t_parse	*temp;
	int		i;
	int		count;

	temp = input;
	i = 0;
	count = cmd_word_count(input);
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			ret[i++] = ft_strdup(temp->arg);
		temp = temp->next;
	}
	ret[count] = NULL;
	return (ret);
}
