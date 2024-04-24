#include "../../../includes/minishell.h"

int	mini_env(t_mini *mini, char **env)
{
	t_env	*mini_env;
	t_env	*new;
	int		i;

	mini_env = malloc(sizeof(t_env));
	if (!mini_env)
		return (1);
	mini_env->value = ft_strdup(env[0]);
	mini_env->next = NULL;
	mini->env = mini_env;
	i = 1;
	while (env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env[i]);
		new->next = NULL;
		mini_env->next = new;
		mini_env = mini_env->next;
		i++;
	}
	return (0);
}

int	env_compare(char *env, char *name)
{
	int	i;

	i = 0;
	while (name[i + 1])
	{
		if (env[i] && env[i] == name[i + 1])
			i++;
		else
			return (0);
	}
	if (env[i] != '=')
		return (0);
	return (1);
}

char	*ft_get_env(char *name, t_mini *mini)
{
	int		i;
	t_env	*temp;

	temp = mini->env;
	i = 0;
	while (temp != NULL)
	{
		if (env_compare(temp->value, name) == 0)
			temp = temp->next;
		else
		{
			while (temp->value[i] != '=')
				i++;
			i++;
			return (ft_strdup(temp->value + i));
		}
	}
	return (NULL);
}

char	*replace_env(char *line, char *envp, char *envp_name, int index)
{
	int		i;
	int		k;
	char	*res;

	i = ft_strlen(line) - ft_strlen(envp_name) + ft_strlen(envp);
	res = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (++i != index)
		res[i] = line[i];
	k = -1;
	while (envp[++k])
		res[i + k] = envp[k];
	k = i + k;
	i = index + ft_strlen(envp_name);
	while (line[i])
		res[k++] = line[i++];
	res[k] = 0;
	free(line);
	return (res);
}

int	ft_valid_env(char c)
{
	if (c >= '0' && c <= '9')
		return (2);
	if (c == '_')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}