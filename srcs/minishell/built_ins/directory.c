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

//unsure if the mini->status is needed

int	cd_handler(t_mini *mini, char **line)
{
	char	buffer[PATH_MAX];
	char	*oldpwd;

	oldpwd = getcwd(buffer, sizeof(buffer));
	if (strarr_len(line) == 2)
	{
		if (chdir(line[1]) == -1)
		{
			print_cmd_error("cd", line[1]);
			mini->status = 1;
		}
		else
		{
			replace_node(mini->env, "OLDPWD", oldpwd);
			replace_node(mini->env, "PWD", getcwd(buffer, sizeof(buffer)));
			mini->status = 0;
		}
	}
	else
	{
		print_cmd_error("cd", "Invalid number of argument");
		mini->status = 1;
	}
	return (1);
}

int	pwd_handler(t_mini *mini)
{
	char	buffer[PATH_MAX];

	if (mini->out != -1)
		ft_putendl_fd(getcwd(buffer, sizeof(buffer)), mini->out);
	else
		ft_putendl_fd(getcwd(buffer, sizeof(buffer)), 1);
	if (errno != 0)
		print_cmd_error("pwd", "");
	mini->status = 0;
	return (1);
}
