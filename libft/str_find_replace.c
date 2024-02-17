#include "libft.h"

char	*str_find_replace(char *line, char *find,char *replace)
{
	int		i;
	int		k;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i + j] == find[j] && find[j])
			j++;
		if (!find[j])
		{
			k = ft_strlen(line) - ft_strlen(find) - ft_strlen(replace);
			result = malloc(sizeof(char) * (k + 1));
			k = -1;
			while (++k < i)
				result[k] = line[k];
			j = i + j;
			while (line[j])
				result[k++] = line[j++];
			result[k] = 0;
			free(line);
			return (result);
		}
		i++;
	}
	return (line);
}