/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:09:11 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/09 18:10:40 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cd_home(t_mini	*mini, char **line)
{
	char	*home;

	if (strarr_len(line) == 1)
	{
		home = ft_get_env("HOME", mini);
		if (!home)
		{
			print_cmd_error("cd Error", 0, "HOME not set");
			mini->status = 1;
			return (0);
		}
		if (chdir(home) == -1)
		{
			free(home);
			print_cmd_error("cd Error", 0, "HOME");
			mini->status = 1;
			return (0);
		}
		free(home);
	}
	return (1);
}

int	cd_handler(t_mini *mini, char **line)
{
	char	buffer[PATH_MAX];
	char	*oldpwd;

	oldpwd = getcwd(buffer, sizeof(buffer));
	if (strarr_len(line) <= 2)
	{
		if (strarr_len(line) == 2 && chdir(line[1]) == -1)
		{
			print_cmd_error("cd Error", 0, line[1]);
			mini->status = 1;
		}
		else if (strarr_len(line) == 1 && chdir(line[1]) == -1)
		{
			if (cd_home(mini, line))
			{
				replace_node(mini->env, "OLDPWD", oldpwd);
				replace_node(mini->env, "PWD", getcwd(buffer, sizeof(buffer)));
				mini->status = 0;
			}
		}
	}
	else
		mini->status = 1;
	return (1);
}

int	pwd_handler(t_mini *mini)
{
	char	buffer[PATH_MAX];
	char	*directory;

	directory = getcwd(buffer, sizeof(buffer));
	if (mini->out != -1 && directory)
		ft_putendl_fd(directory, mini->out);
	else if (directory)
		ft_putendl_fd(directory, 1);
	if (directory == NULL)
	{
		print_cmd_error("pwd Error", 0, "");
		mini->status = 1;
	}
	else
		mini->status = 0;
	return (1);
}
