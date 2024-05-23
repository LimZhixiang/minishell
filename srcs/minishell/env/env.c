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

int	dfl_env(t_mini *mini)
{
	char	*pwd;
	char	*temp;

	temp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", temp);
	if (!pwd || !temp)
		exit (1);
	export(mini, pwd);
	export(mini, "SHLVL=1");
	mini->list = add_export_node(mini->list, create_export_node("SHLVL", "1"));
	mini->list = add_export_node(mini->list, create_export_node("PWD", pwd));
	if (!mini->list)
		exit (1);
	free(pwd);
	free(temp);
	return (1);
}

int	init_mini_env(t_mini *mini, char **env)
{
	char	*name;
	char	*value;
	int		i;

	mini->env = NULL;
	mini->list = NULL;
	i = 0;
	if (!env[i])
		dfl_env(mini);
	while (env[i])
	{
		mini->env = add_node(mini->env, create_node(env[i]));
		name = get_envp_name(env[i]);
		value = get_envp_value(env[i]);
		mini->list =
		add_export_node(mini->list, create_export_node(name, value));
		if (!mini->list || !mini->env || !name || !value)
			exit(1);
		free(name);
		free(value);
		i++;
	}
	return (1);
}

int	env_compare(char *env, char *name)
{
	int	i;

	i = 0;
	if (name[0] == '$')
		name++;
	while (name[i] && env[i])
	{
		if (env[i] != name[i])
			return (0);
		i++;
	}
	if (env[i] != '=')
		return (0);
	return (1);
}

char	*ft_get_env(char *name, t_mini *mini)
{
	int		i;
	t_env	*temp;

	temp = mini->env;
	while (temp != NULL)
	{
		i = 0;
		if (env_compare(temp->value, name) == 0)
			temp = temp->next;
		else
		{
			while (temp->value[i] != '=')
				i++;
			i++;
			return (ft_strdup(temp->value + i));
		}
	}
	return (NULL);
}

char	*replace_env(char *line, char *envp, char *envp_name, int index)
{
	int		i;
	int		k;
	char	*res;

	i = ft_strlen(line) - ft_strlen(envp_name) + ft_strlen(envp);
	res = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (++i != index)
		res[i] = line[i];
	k = 0;
	while (envp && envp[k])
	{
		res[i + k] = envp[k];
		k++;
	}
	k = i + k;
	i = index + ft_strlen(envp_name);
	while (line[i])
		res[k++] = line[i++];
	res[k] = '\0';
	free(line);
	return (res);
}

int	ft_valid_env(char c)
{
	if (c >= '0' && c <= '9')
		return (2);
	if (c == '_')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '?')
		return (-1);
	return (0);
}
