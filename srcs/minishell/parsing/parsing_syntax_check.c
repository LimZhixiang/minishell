/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_check                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	check_syntax(t_mini *mini)
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
				print_syntax_error(temp->arg);
			else if (error == 2)
				print_syntax_error("newline");
			else
				print_syntax_error(temp->next->arg);
			mini->status = 2;
			return (mini->status);
		}
		temp = temp->next;
	}
	return (0);
}

int	check_quote_syntax(char *line)
{
	if (ft_quote(line, ft_strlen(line)) != 0)
	{
		ft_putstr_fd("Quotes not closed properly, syntax error\n", 2);
		return (0);
	}
	return (1);
}
