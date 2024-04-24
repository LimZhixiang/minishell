#include "../../../includes/minishell.h"

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

void	tokenization(char *new, t_mini *mini)
{
	char	**split;
	t_parse	*temp;
	int		cmd_flag;
	int		i;

	i = 0;
	cmd_flag = 1;
	split = ft_mini_split(new);
	//printf for testing
	printf("\033[0;31m\n2.[TOKENIZATION]: CREATE STRUCT AND TOKENIZE:\n1 = CMD\n2 = ARG\n3 = (|)PIPE\n4 = (>)OUTPUT\n5 = (>>)APPEND\n6 = (<)INPUT\n7 = (<<)HDOC\n\033[0m");
	
	if (split == NULL)
		return ;
	temp = ft_newnode(split[i++]);
	temp->type = operator_type(temp->arg, &cmd_flag);
	//testing rmb to remove
	printf("[Node%i]: \033[0;32m%i, %s\n\033[0m", i - 1, temp->type, temp->arg);
	mini->input = temp;
	while (split[i])
	{
		split[i] = ft_var_exp(split[i], mini);
		temp->next = ft_newnode(split[i++]);
		temp->next->type = operator_type(temp->next->arg, &cmd_flag);
		//testing rmb to remove
		printf("[Node%i]: \033[0;32m%i, %s \n\033[0m", i - 1, temp->next->type, temp->next->arg);
		temp = temp->next;
	}
	//testing rmb to remove
	printf("\n");
}