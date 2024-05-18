/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:07:39 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/08 16:21:56 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_node(t_env *head, t_env *new)
{
	t_env	*temp;

	temp = head;
	if (!head)
		head = new;
	while (temp->next != NULL)
		temp = temp->next;
	if (new != NULL)
		temp->next = new;
}

void	replace_node(t_env *node, char *env_name, char *value)
{
	t_env	*temp;
	char	*name;
	char	*holder;

	temp = node;
	while (temp)
	{
		holder = get_envp_name(temp->value);
		if (ft_strcmp(holder, env_name))
		{
			name = ft_strjoin(holder, "=");
			free(holder);
			holder = name;
			name = ft_strjoin(holder, value);
			if (name)
			{
				free(temp->value);
				temp->value = name;
			}
		}
		free(holder);
		temp = temp->next;
	}
}

t_env	*del_curr_node(t_env *prev, t_env *del, t_mini *mini)
{
	t_env	*head;

	prev->next = del->next;
	if (prev == del)
	{
		head = del->next;
		free(del->value);
		free(del);
		mini->env = head;
		return (head);
	}
	free(del->value);
	free(del);
	return (prev);
}

t_env	*create_node(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		print_cmd_error("malloc Error", 0, "");
	else
	{
		new->value = ft_strdup (value);
		if (new->value == NULL)
		{
			free(new);
			print_cmd_error("malloc", "");
			return (NULL);
		}
		new->next = NULL;
	}
	return (new);
}
