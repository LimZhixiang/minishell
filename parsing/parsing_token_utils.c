#include "../minishell.h"

int	operator_type(char *arg, int *CMD_FLAG)
{
	int	type;

	type = ARG;
	if (ft_strcmp("|", arg) == 1)
		type = PIPE;
	else if (ft_strcmp(">", arg) == 1)
		type = OUTPUT;
	else if (ft_strcmp(">>", arg) == 1)
		type = APPEND;
	else if (ft_strcmp("<", arg) == 1)
		type = INPUT;
	else if (ft_strcmp("<<", arg) == 1)
		type = HDOC;
	else if (*CMD_FLAG == 1)
		type = CMD;
	if (type != ARG)
	{
		if (type == PIPE)
			*CMD_FLAG = 1;
		else if (*CMD_FLAG == 1)
			*CMD_FLAG = 0;
	}
	return (type);
}

int	wrd_count(char *new)
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


int	mini_letters(char *new, int i, int flag)
{
	int quote;
	int	count;

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
		}
		count++;
		i++;
	}
	if (flag == 1)
		return (count);
	else
		return (i);
}

t_parse	*ft_newnode(char *content)
{
	t_parse	*new;
	new = malloc(sizeof(t_parse));
	if (!new)
		return (0);
	new->arg = ft_strdup(content);
	new->next = NULL;
	return (new);
}