#include "../minishell.h"

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

// int	mini_letters(char *new, int i, int flag)
// {
// 	int quote;
// 	int	count;

// 	count = 0;
// 	quote = 0;
// 	while (new[i] && (new[i] != ' ' || quote != 0))
// 	{
// 		if ((new[i] == '\'' || new[i] == '\"'))
// 		{
// 			if (quote == 0)
// 				quote = ft_quote_c(new[i]);
// 			else if (quote == ft_quote_c(new[i]))
// 				quote = 0;
// 			count++;
// 		}
// 		else
// 			count++;
// 		i++;
// 	}
// 	if (flag == 1)
// 		return (count);
// 	else
// 		return (i);
// }

t_parse	*ft_newnode(char *content)
{
	t_parse	*new;
	new = malloc(sizeof(t_parse));
	if (!new)
		return (0);
	new->arg = content;
	new->next = NULL;
	return (new);
}