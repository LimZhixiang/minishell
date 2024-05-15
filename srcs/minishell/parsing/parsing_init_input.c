/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parse	*ft_newnode(char *content, t_parse *prev)
{
	t_parse	*new;

	new = malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->arg = ft_strdup(content);
	if (new->arg == NULL)
	{
		free(new);
		return (NULL);
	}
	new->prev = prev;
	new->next = NULL;
	return (new);
}

int	init_input(char **split, t_mini *mini)
{
	t_parse	*temp;
	int		cmd_flag;
	int		i;

	cmd_flag = 1;
	i = 0;
	temp = ft_newnode(split[i++], NULL);
	temp->arg = ft_var_exp(temp->arg, mini, 0);
	if (temp == NULL)
		return (0);
	temp->type = tokenization(temp, &cmd_flag);
	mini->input = temp;
	while (split[i])
	{
		temp->next = ft_newnode(split[i++], temp);
		temp->next->arg = ft_var_exp(temp->next->arg, mini, 0);
		if (temp->next == NULL)
		{
			free_str_arr(split);
			ft_free_all(mini, RE_SHELL);
			return (0);
		}
		temp->next->type = tokenization(temp->next, &cmd_flag);
		temp = temp->next;
	}
	free_str_arr(split);
	return (1);
}
