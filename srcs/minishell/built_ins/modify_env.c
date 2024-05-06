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

}

t_env	*create_node(t_env *head)
{
}