/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_line_env_heredoc(char *line, t_mini *mini, int i, int j)
{
	char	*env_name;
	char	*env_result;

	env_name = ft_substr(line, i, j);
	if (env_name == NULL)
		return (NULL);
	env_result = ft_get_env(env_name, mini);
	line = replace_env(line, env_result, env_name, i);
	free(env_name);
	if (env_result != NULL)
		free(env_result);
	return (line);
}

char	*here_doc_exp(char *arg, t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && ft_valid_env(arg[i + 1]) != 0)
		{
			j = 1;
			while (ft_valid_env(arg[i + j]) > 0)
				j++;
			if (ft_valid_env(arg[i + j]) == -1 && j == 1)
				arg = get_status_code(arg, mini, i);
			else
				arg = get_line_env_heredoc(arg, mini, i, j);
			if (arg == NULL)
				return (NULL);
			i = -1;
		}
		i++;
	}
	return (arg);
}
