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

void	free_t_parse(t_parse *ptr, int type)
{
	t_parse	*current;
	t_parse	*next;

	if (ptr == NULL)
		return ;
	current = ptr;
	while (current != NULL)
	{
		next = current->next;
		if (current->heredoc != NULL)
		{
			if (type != HDOC && access(current->heredoc, F_OK) == 0)
				unlink(current->heredoc);
			free(current->heredoc);
		}
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

void	free_t_export(t_export *list)
{
	t_export	*current;
	t_export	*next;

	if (list == NULL)
		return ;
	current = list;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_execution(t_mini *mini, int type)
{
	free_t_parse(mini->input, type);
	free_t_export(mini->list);
	free_t_env(mini->env);
	close(mini->term_in);
	close(mini->term_out);
	close(mini->std_err);
	if (mini->in != -1)
		close(mini->in);
	if (mini->out != -1)
		close(mini->out);
	free(mini->user_input);
	free(mini);
}

void	ft_free_all(t_mini *mini, int state)
{
	if (state == EXIT_SHELL)
	{
		close(mini->term_in);
		close(mini->term_out);
		close(mini->std_err);
		if (mini->in != -1)
			close(mini->in);
		if (mini->out != -1)
			close(mini->out);
		free_t_env(mini->env);
		free_t_export(mini->list);
		free (mini->user_input);
		free (mini);
		return ;
	}
	if (mini->exit == 0)
		free(mini->user_input);
	free_t_parse(mini->input, 0);
	mini->input = NULL;
}
