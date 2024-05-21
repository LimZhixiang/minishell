/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_node_utils.c           	                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:07:39 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/08 16:21:56 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_export	*add_export_node(t_export *head, t_export *new)
{
	t_export	*temp;

	temp = head;
	if (!head)
		return (new);
	while (temp->next != NULL)
		temp = temp->next;
	if (new != NULL)
		temp->next = new;
	return (head);
}

void	replace_export_node(t_export *node, char *env_name, char *value)
{
	t_export	*temp;
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

// t_export	*del_curr_node(t_export *prev, t_export *del, t_mini *mini)
// {
// 	t_export	*head;

// 	prev->next = del->next;
// 	if (prev == del)
// 	{
// 		head = del->next;
// 		free(del->value);
// 		free(del);
// 		mini->env = head;
// 		return (head);
// 	}
// 	free(del->value);
// 	free(del);
// 	return (prev);
// }

t_export	*create_export_node(char *value)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		print_cmd_error("malloc Error", 0, "");
	else
	{
		new->value = ft_strdup(value);
		if (new->value == NULL)
		{
			free(new);
			print_cmd_error("malloc Error", 0, "");
			return (NULL);
		}
		new->next = NULL;
	}
	return (new);
}

t_export	*del_export_node(t_export *prev, t_export *del, t_mini *mini)
{
	if (del == prev)
	{
		mini->env = del->next;
		prev = del->next;
	}
	else
		prev->next = del->next;
	free(del->value);
	free(del);
	return (prev);
}
