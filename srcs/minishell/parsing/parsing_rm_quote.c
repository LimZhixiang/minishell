#include "../../../includes/minishell.h"

void	cpy_rm_quote(char *result, char *current)
{
	int	quote;
	int	i;
	int	j;

	i = 0;
	j = 0;
	quote = 0;
	while (current[i])
	{
		if (current[i] == '\'' || current[i] == '\"')
		{
			if (quote == 0)
				quote = ft_quote_c(current[i]);
			else if (quote == ft_quote_c(current[i]))
				quote = 0;
			else
				result[j++] = current[i];
			i++;
		}
		else
			result[j++] = current[i++];
	}
	result[j] = '\0';
}

int	rm_quote_letters(char *new)
{
	int quote;
	int	count;
	int	i;

	i = 0;
	count = 0;
	quote = 0;
	while (new[i])
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
	return (count);
}

char	*rm_node_quote(char *current)
{
	char	*result;

	result = malloc(sizeof(char) * (rm_quote_letters(current) + 1));
	if (!result)
		return (NULL);
	cpy_rm_quote(result, current);
	return (result);
}

void	ft_rm_quotes(t_mini *mini)
{
	t_parse	*temp;
	char	*result;

	temp = mini->input;
	while (temp)
	{
		result = rm_node_quote(temp->arg);
		if (!result)
			free (mini);
		free(temp->arg);
		temp->arg = ft_strdup(result);
		free(result);
		temp = temp->next;
	}
}