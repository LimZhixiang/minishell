#include "../../../includes/minishell.h"

void	add_node(t_env *head, t_env *new)
{
	t_env	*temp;

	temp = head;
	
	while (temp->next != NULL)
		temp = temp->next;
	if (new != NULL)
		temp->next = new;
}

t_env	*del_curr_node(t_env *prev, t_env *del)
{
	prev->next = del->next;
	free(del);
	return (prev);
}

t_env	*create_node(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		print_cmd_error("malloc", "");
	else
	{
		new->value = ft_strdup (value);
		new->next = NULL;
	}
	return (new);
}
