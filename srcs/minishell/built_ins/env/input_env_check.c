#include "../../../../includes/minishell.h"

int	env_found(char *line)
{
	char	*temp;

	temp = ft_strchr(line, '$');
	if (!temp)
		return (0);
	if (temp[1] != ' ' && temp[1])
		return (1);
	if (ft_strchr(temp + 1, '$'))
		return (1);
	return (0);
}

char	*invalid_env(char *line)
{
	int	i;
	int index;
	char	*temp;

	i = 0;
	while (line[i] != '$')
		i++;
	index = i;
	while (line[i] != ' ' && line[i])
		i++;
	i  = i - index;
	temp = ft_substr((const char *)line, index, i);
	line = str_find_replace(line, temp, "");
	free(temp);
	return(line);
}