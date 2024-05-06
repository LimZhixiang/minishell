/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (wrd_count(new) != 0)
		result = malloc(sizeof(char *) * (wrd_count(new) + 1));
	if (wrd_count(new) == 0 || !result)
		return (NULL);
	while (arg < wrd_count(new))
	{
		while (new[i] == ' ')
			i++;
		result[arg] = mini_cpy_letters(new, i);
		if (result[arg] == NULL)
		{
			free_str_arr(result);
			return (NULL);
		}
		arg++;
		i = mini_letters(new, i, 2);
	}
	result[wrd_count(new)] = NULL;
	return (result);
}

int	syntax_error_type(t_parse *input)
{
	int		error;
	t_parse	*temp;

	temp = input;
	error = 0;
	if (temp->type == PIPE)
	{
		if (temp->prev == NULL || temp->prev->type >= PIPE
			|| temp->next == NULL || temp->next->type >= PIPE)
			error = 1;
	}
	if (temp->type > PIPE)
	{
		if (temp->next == NULL)
			error = 2;
		else if (temp->next->type >= PIPE)
			error = 3;
	}
	return (error);
}

void	check_syntax(t_mini *mini)
{
	t_parse	*temp;
	int		error;

	error = 0;
	temp = mini->input;
	while (temp && error == 0)
	{
		error = syntax_error_type(temp);
		if (error != 0)
		{
			if (error == 1)
				printf("syntax error near \'%s\'", temp->arg);
			else if (error == 2)
				printf("syntax error near \'newline\'");
			else
				printf("syntax error near \'%s\'", temp->next->arg);
			mini->status = 2;
			return ;
		}
		temp = temp->next;
	}
}

int	init_input(char **split, t_mini *mini)
{
	t_parse	*temp;
	int		cmd_flag;
	int		i;

	cmd_flag = 0;
	i = 0;
	temp = ft_newnode(split[i++], NULL);
	if (temp == NULL)
		return (0);
	temp->type = operator_type(temp, &cmd_flag);
	mini->input = temp;
	while (split[i])
	{
		split[i] = ft_var_exp(split[i], mini);
		temp->next = ft_newnode(split[i++], temp);
		if (temp->next == NULL)
		{
			ft_free_all(mini, RE_SHELL);
			return (0);
		}
		temp->next->type = operator_type(temp->next, &cmd_flag);
		temp = temp->next;
	}
	return (1);
}

int	tokenization(char *new, t_mini *mini)
{
	char	**split;

	split = ft_mini_split(new);
	free(new);
	if (split == NULL)
		return (0);
	if (!init_input(split, mini))
	{
		free_str_arr(split);
		return (0);
	}
	free_str_arr(split);
	return (1);
}
