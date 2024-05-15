/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_t_parse(t_parse *ptr)
{
	t_parse	*current;
	t_parse	*next;

	if (ptr == NULL)
		return ;
	current = ptr;
	while (current != NULL)
	{
		next = current->next;
		free(current->arg);
		free(current);
		current = next;
	}
}

void	free_t_env(t_env *ptr)
{
	t_env	*current;
	t_env	*next;

	if (ptr == NULL)
		return ;
	current = ptr;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	ft_free_all(t_mini *mini, int state)
{
	if (state == EXIT_SHELL)
	{
		close(mini->term_in);
		close(mini->term_out);
		if (mini->in != -1)
			close(mini->in);
		if (mini->out != -1)
			close(mini->out);
		close(0);
		close(1);
		free_t_env(mini->env);
		free (mini->user_input);
		free (mini);
		return ;
	}
	if (mini->exit == 0)
		free(mini->user_input);
	free_t_parse(mini->input);
	mini->input = NULL;
}
