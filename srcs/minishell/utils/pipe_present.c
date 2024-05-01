#include "../../../includes/minishell.h"

void	pipe_present(t_mini *mini, t_parse *head)
{
	t_parse	*node;

	node = head;
	while (node)
	{
		if (node->type == PIPE)
		{
			mini->pipe = 1;
			return ;
		}
		node = node->next;
	}
	mini->pipe = 0;
}
