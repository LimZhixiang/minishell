/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_status_code(char *line, t_mini *mini, int i)
{
	char	*status_code;

	status_code = ft_itoa(mini->status);
	if (status_code == NULL)
		return (NULL);
	line = replace_env(line, status_code, "$?", i);
	free(status_code);
	return (line);
}

//original
// char	*get_line_env(char *line, t_mini *mini, int i, int j)
// {
// 	char	*env_name;
// 	char	*env_result;

// 	env_name = ft_substr(line, i, j);
// 	if (env_name == NULL)
// 		return (NULL);
// 	env_result = ft_get_env(env_name, mini);
// 	line = replace_env(line, env_result, env_name, i);
// 	free(env_name);
// 	if (env_result != NULL)
// 		free(env_result);
// 	return (line);
// }

//edited
char	*quote_mal_cpy(char *temp)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(temp) + 3);
	if (!ret)
		return (NULL);
	ret[0] = '\'';
	while (temp[i])
	{
		ret[i + 1] = temp[i];
		i++;
	}
	ret[i + 1] = '\'';
	ret[i + 2] = '\0';
	free(temp);
	return (ret);
}

char	*join_split(char **split, char *env_result)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (split[i])
		j = j + ft_strlen(split[i++]);
	new = malloc(sizeof(char) * (j + (i - 1) + 1));
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
			new[k++] = split[i][j++];
		if (split[i + 1])
			new[k++] = ' ';
		i++;
	}
	new[k] = '\0';
	free(env_result);
	return (new);
}

char	*ft_add_quotes(char *env_result)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(env_result, ' ');
	if (!temp || !env_result)
		return (NULL);
	while (temp[i])
	{
		temp[i] = quote_mal_cpy(temp[i]);
		i++;
	}
	env_result = join_split(temp, env_result);
	free_str_arr(temp);
	return (env_result);
}

char	*get_line_env(char *line, t_mini *mini, int i, int j)
{
	char	*env_name;
	char	*env_result;

	env_name = ft_substr(line, i, j);
	if (env_name == NULL)
		return (NULL);
	env_result = ft_get_env(env_name, mini);
	if (ft_quote(line, i) == 0)
		env_result = ft_add_quotes(env_result);
	line = replace_env(line, env_result, env_name, i);
	free(env_name);
	if (env_result != NULL)
		free(env_result);
	return (line);
}
//edited

char	*ft_var_exp(char *arg, t_mini *mini, int flag)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		if (ft_quote(arg, i) != 1 && arg[i] == '$'
			&& ft_valid_env(arg[i + 1]) != 0)
		{
			if (flag == 1 && i != 0 && arg[i - 1] == '=')
			{
				i++;
				continue ;
			}
			j = 1;
			while (ft_valid_env(arg[i + j]) > 0)
				j++;
			if (ft_valid_env(arg[i + j]) == -1 && j == 1)
				arg = get_status_code(arg, mini, i);
			else
				arg = get_line_env(arg, mini, i, j);
			if (arg == NULL)
				return (NULL);
		}
		else
			i++;
	}
	return (arg);
}

// char	**ft_split_var_exp(char **split, t_mini *mini)
// {
// 	int	i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		split[i] = ft_var_exp(split[i], mini);
// 		if (split[i] == NULL)
// 		{
// 			free_str_arr(split);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (split);
// }
