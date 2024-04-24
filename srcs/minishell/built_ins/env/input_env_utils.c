#include "../../../../includes/minishell.h"

int	find_env(char *line, char *wrd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (wrd[j] == line[i + j])
		{
			if (wrd[j + 1] == 0) 
				if (line[i + j + 1] == ' ' || line[i + j + 1] == 0)
					return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}

char	*get_envp_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (str[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 2));
	if (!res)
		return (NULL);
	res[0] = '$';
	i = 0;
	while (str[i] != '=')
	{
		res[i + 1] = str[i];
		i++;
	}
	res[i + 1] = 0;
	return (res);
}

char	*get_envp_value(char *str)
{
	int		i;
	int		l;
	char	*res;

	i = 0;
	res = NULL;
	while (str[i] != '=')
		i++;
	l = ft_strlen(str);
	res = malloc(sizeof(char) * (l - i));
	if (!res)
		return (NULL);
	l = 0;
	while (str[++i])
		res[l++] = str[i];
	res[l] = 0;
	return (res);
}