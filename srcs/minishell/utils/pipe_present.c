#include "../../../includes/minishell.h"

int	pipe_present(t_parse *head)
{
	t_parse	*node;

	node = head;
	while (node)
	{
		if (node->type == PIPE)
			return (1);
		node = node->next;
	}
	return (0);
}
