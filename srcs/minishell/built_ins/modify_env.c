#include "../../../includes/minishell.h"

t_env	*add_node(t_env *head, t_env *new)
{
	t_env	*temp;

	temp = head;
	while (temp != NULL)
		temp = temp->next;
	temp = new;
}

t_env	*remove_node(t_env *head, t_env *del)
{
	t_env	*temp;
	t_env	*iter;

	iter = head;
	while (iter)
	{
		if (iter)
		iter = iter->next;
	}
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