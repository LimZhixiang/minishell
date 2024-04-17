#include "minishell.h"

int	get_env(t_mini *mini, char **env)
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

void	print_env(t_mini *mini)
{
	while (mini->env)
	{
		printf("%s\n", mini->env->value);
		mini->env = mini->env->next;
	}
}

int	is_sep(char c)
{
	if (c == '|')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '<')
		return (3);
	return (0);
}

int	ft_quote_c(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	ft_quote(char *line, int i)
{
	int	j;
	int	quote;

	quote = 0;
	j = 0;
	while (line && line[j] && j != i)
	{
		if (quote == 0 && line[j] == '\'')
			quote = 1;
		else if (quote == 0 && line[j] == '\"')
			quote = 2;
		else if (quote == 1 && line[j] == '\'')
			quote = 0;
		else if (quote == 2 && line[j] == '\"')
			quote = 0;
		j++;
	}
	return (quote);
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

char	*ft_var_count(char *new, t_mini *mini)
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

void	filter_quotes(char *new)
{
	int	i;
	int j;
	int	quotes;
	int	count;
	char *temp;

	i = 0;
	quotes = 0;
	count = 0;
	while (new[i])
	{
		if (ft_quote(new, i + 1) != quotes)
			quotes = ft_quote(new, i + 1);
		else
			count++;
		i++;
	}
	temp = malloc(sizeof(char) * count + 1);
	if (!temp)
		return ;
	i = -1;
	j = 0;
	while (new[++i])
	{
		if (ft_quote(new, i + 1) != quotes)
			quotes = ft_quote(new, i + 1);
		else
			temp[j++] = new[i];
	}
	temp[j] = '\0';
}

int	mini_wrd(char *new)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	while(new[i])
	{
		if (new[i] != ' ' && ft_quote(new, i) == 0)
		{
			word++;
			while (new[i] && (new[i] != ' ' || ft_quote(new, i) != 0))
				i++;
		}
		else
			i++;
	}
	return (word);
}

char	**ft_mini_split(char *new)
{
	char	**result;

	result = malloc(sizeof(char *) * (mini_wrd(new) + 1));
	if (!new || !result)
		return (NULL);
	while (new[i])
	{
		while (new[i])
		{
			if (ft_quote(new, i + 1) != quotes)
				quotes = ft_quote(new, i + 1);
			else
				count++;
			i++;
		}
	}
	result[mini_wrd(new)] = NULL;
	return (result);
}

char	*ft_count_letters(char *new, int i)
{
	int quote;
	int	count;
	char	*ret;

	count = 0;
	quote = 0;
	while (new[i] && (new[i] != ' ' || quote != 0))
	{
		if ((new[i] == '\'' || new[i] == '\"'))
		{
			if (quote == 0)
				quote = ft_quote_c(new[i]);
			else if (quote == ft_quote_c(new[i]))
				quote = 0;
			else
				count++;
		}
		else
			count++;
		i++;
	}
	ret = malloc(sizeof(char) * count + 1);
	return (ret);
}

void	shell_split(char *new)
{
	char	**split;
	int		i;
	int		j;
	int		quote;

	j = 0;
	i = -1;
	quote = 0;
	split = ft_mini_split(new);
	while (new[++i])
	{
		while (split[j])
		{
			if (ft_quote_c(new[i]) != quote)
				quote = ft_quote_c(new[i]);
			split[j] = ft_count_letters(new, i);
			j++;
		}
	}
}

int	parsing(char *line, t_mini *mini)
{
	char	*new;

	new = ft_alloc_space(line);
	ft_space_line(new, line);
	new = ft_var_count(new, mini);
	shell_split(new);
	// tokenization()
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	int		exit = 0;
	(void)argc;
	(void)argv;

	mini = malloc(sizeof(t_mini));
	get_env(mini, envp);
	while (exit == 0)
	{
		input = readline("minishell: ");
		parsing(input, mini);
		free (input);
	}
	return (0);
}