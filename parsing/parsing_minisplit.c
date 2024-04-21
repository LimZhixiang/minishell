#include "../minishell.h"

void	ft_copy_letters(char *ret, char *new, int i)
{
	int	j;
	int	quote;

	quote = 0;
	j = 0;
	while (new[i] && (new[i] != ' ' || quote != 0))
	{
		if ((new[i] == '\'' || new[i] == '\"'))
		{
			if (quote == 0)
				quote = ft_quote_c(new[i]);
			else if (quote == ft_quote_c(new[i]))
				quote = 0;
		}
		ret[j++] = new[i++];
	}
	ret[j] = '\0';
}

char	*mini_cpy_letters(char *new, int i)
{
	char	*ret;

	ret = malloc(sizeof(char) * mini_letters(new, i, 1) + 1);
	if (!ret)
		return (NULL);
	ft_copy_letters(ret, new, i);
	return (ret);
}

char	**ft_mini_split(char *new)
{
	char	**result;
	int		i;
	int		arg;

	arg = 0;
	i = 0;
	result = malloc(sizeof(char *) * (wrd_count(new) + 1));
	if (!new || !result || wrd_count(new) == 0)
		return (NULL);
	while (arg < wrd_count(new))
	{
		while (new[i] == ' ')
			i++;
		result[arg++] = mini_cpy_letters(new, i);
		i = mini_letters(new, i, 2);
	}
	result[wrd_count(new)] = NULL;
	return (result);
}

void	input_init(char *new, t_mini *mini)
{
	char	**split;
	t_parse	*temp;
	int		i;

	i = 0;
	split = ft_mini_split(new);
	if (split != NULL)
	{
		temp = ft_newnode(split[i++]);
		mini->input = temp;
	}
	else
		return;
	while (split[i])
	{
		temp->next = ft_newnode(split[i]);
		temp = temp->next;
		i++;
	}
}