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

int	operator_type(char *arg, int *CMD_FLAG)
{
	int	type;

	type = 0;
	if (ft_strcmp("|", arg) == 1)
		type = PIPE
	else if (ft_strcmp(">", arg) == 1)
		type = OUTPUT;
	else if (ft_strcmp(">>", arg) == 1)
		type = APPEND;
	else if (ft_strcmp("<", arg) == 1)
		type = INPUT;
	else if (ft_strcmp("<<", arg) == 1)
		type = HDOC;
	if (*CMD_FLAG == 1 && type == 0)
		type = CMD;
	if (type != 0)
	{
		if (type == PIPE)
			*CMD_FLAG = 1;
		else if (*CMD_FLAG == 1)
			*CMD_FLAG = 0;
	}
	return (type);
}

// void	tokenization(t_mini *mini)
// {
// 	t_parse *temp;
// 	int		next_cmd;

// 	next_cmd = 1;
// 	temp = mini->input;
// 	if (mini != NULL)
// 	{
// 		while (temp != NULL)
// 		{
// 			if (next_cmd == 1)
// 			{
// 				temp->type = CMD;
// 				next_cmd = 0;
// 			}
// 			else if (operator_type(temp->arg) == 3)
// 			{
// 				temp->type = operator_type(temp->arg);
// 				next_cmd = 1;
// 			}
// 			else
// 				temp->type = operator_type(temp ->arg);
// 			printf("%s, %i\n", temp->arg, temp->type);
// 			temp = temp->next;
// 		}
// 	}
// }

void	ft_create_node(char *new, t_mini *mini)
{
	char	**split;
	t_parse	*temp;
	int		cmd_flag;
	int		i;

	i = 0;
	cmd_flag = 1;
	split = ft_mini_split(new);
	if (split != NULL)
	{
		temp = ft_newnode(split[i]);
		temp->type = operator_type(temp->arg, &cmd_flag);
		mini->input = temp;
		i++;
	}
	while (split[i])
	{
		temp->next = ft_newnode(split[i++]);
		temp->next->type = operator_type(temp->next->arg, &cmd_flag);
		temp = temp->next;
		i++;
	}
}

// void tokenization(t_mini *mini)
// {
// 	t_parse	*temp;
// 	int	i;

// 	i = 0;
// 	temp = mini->env;
// 	while (temp != NULL)
// 	{
// 		temp->type = operator_type(temp->arg, i);
// 		temp = temp->next;
// 	}
// }

int	parsing(char *line, t_mini *mini)
{
	char	*new;

	new = ft_alloc_space(line);
	ft_space_line(new, line);
	new = ft_var_exp(new, mini);
	ft_create_node(new, mini);
	// tokenization(mini);
	// input_init(new, mini);
	return (1);
}