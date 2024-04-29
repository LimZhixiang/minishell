#include "../../../includes/minishell.h"

int	env_node_count(t_env *env)
{
	t_env	*temp;
	int		i;

	temp = env;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**get_env_arr(t_mini *mini)
{
	t_env	*temp;
	char	**ret;
	int		i;

	temp = mini->env;
	i = 0;
	ret = malloc(sizeof(char *) * (env_node_count(temp) + 1));
	if (!ret)
		return (NULL);
	while (temp != NULL)
	{
		ret[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	ret[i] = NULL;
	return(ret);
}