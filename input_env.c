#include "minishell.h"

char	*convert_env(char *line, char **envp)
{
	int	i;
	int	index;
	char	*envp_name;

	i = 0;
	while (envp[i])
	{
		envp_name = get_envp_name(envp[i]);
		index = find_env(line, envp_name);
		if (index != -1)
			line = replace_env(line, envp[i], envp_name, index);
		free(envp_name);
		i++;
	}
	while (env_found(line))
		line = invalid_env(line);
	return (line);
}

char	*replace_env(char *line, char *envp, char *envp_name, int index)
{
	int		i;
	int		k;
	char	*envp_value;
	char	*res;

	envp_value = get_envp_value(envp);
	i = ft_strlen(line) - ft_strlen(envp_name) + ft_strlen(envp_value);
	res = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (++i != index)
		res[i] = line[i];
	k = -1;
	while (envp_value[++k])
		res[i + k] = envp_value[k];
	k = i + k;
	i = index + ft_strlen(envp_name);
	while (line[i])
		res[k++] = line[i++];
	res[k] = 0;
	free(envp_value);
	free(line);
	return (res);
}