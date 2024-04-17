#include "../minishell.h"

char	*ft_var_exp(char *new, t_mini *mini)
{
	int		i;
	int		j;
	char	*name;
	char	*result;

	i = -1;
	while (new[++i])
	{
		if (ft_quote(new, i) != 1 && new[i] == '$'
			&& ft_valid_env(new[i + 1]) != 0)
		{
			j = 1;
			while (ft_valid_env(new[i + j]) != 0)
				j++;
			name = ft_substr(new, i, j);
			result = ft_get_env(name, mini);
			new = replace_env(new, result, name, i);
			i = i + ft_strlen(result);
			free(name);
			free(result);
		}
	}
	return (new);
}

int	ft_space_line(char *new, char *line)
{
	int	i;
	int	j;
	int	sep;

	sep = 0;
	i = 0;
	j = 0;
	while (new && line[i])
	{
		sep = is_sep(line[i]);
		if (sep != 0 && ft_quote(line, i) == 0 && i > 0)
		{
			if (line[i - 1] != ' ' && is_sep(line[i - 1]) != sep)
				new[j++] = ' ';
			new[j++] = line[i++];
			if (sep != 1 && is_sep(line[i]) == sep)
				new[j++] = line[i++];
			if (!ft_strchr(" \0", line[i]))
				new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	return (1);
}

char	*ft_alloc_space(char *line)
{
	int		i;
	int		space;
	int		sep;
	char	*new;

	space = 0;
	i = 0;
	while (line[i])
	{
		sep = is_sep(line[i]);
		if (sep != 0 && ft_quote(line, i) == 0 && i > 0)
		{
			if (!ft_strchr(" ", line[i - 1]) && is_sep(line[i - 1]) != sep)
				space++;
			if (sep != 1 && is_sep(line[i + 1]) == sep)
				i++;
			if (!ft_strchr(" \0", line[i + 1]))
				space++;
		}
		i++;
	}
	new = malloc(sizeof(char) * (i + space + 1));
	if (!new)
		return (NULL);
	return (new);
}

int	parsing(char *line, t_mini *mini)
{
	char	*new;

	new = ft_alloc_space(line);
	ft_space_line(new, line);
	new = ft_var_exp(new, mini);
	input_init(new, mini);
	// tokenization(mini);
	return (1);
}