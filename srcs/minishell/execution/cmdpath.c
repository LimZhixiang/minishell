/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:10:25 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:10:26 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*extract_path(char **env)
{
	char	*path;
	char	*pattern;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = "";
	pattern = "PATH=\0";
	while (env[i])
	{
		while (env[i][j] == pattern[j])
		{
			if (!pattern[++j])
			{
				path = ft_strdup(env[i]);
				break ;
			}
		}
		j = 0;
		i++;
	}
	if (!path)
		print_cmd_error("malloc Error", 0, "");
	return (path);
}

static char	*check_cmd(char *envpath, char *cmd)
{
	char	*addslash;
	char	*path;	
	char	**paths;
	int		i;

	path = NULL;
	if (!envpath)
		return (NULL);
	paths = ft_split(envpath, ':');
	if (paths == NULL)
		print_cmd_error("malloc Error", 0, "");
	i = -1;
	while (paths && paths[++i])
	{
		addslash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(addslash, cmd);
		free(addslash);
		if (!access(path, F_OK | X_OK))
			break ;
		free(path);
		path = NULL;
	}
	free_str_arr(paths);
	return (path);
}

char	*getcmdpath(char *cmdarg, char *envpath)
{
	char	*cmdpath;

	cmdpath = NULL;
	if (cmdarg != NULL)
		cmdpath = check_cmd(envpath, cmdarg);
	if (!cmdpath)
		print_cmd_error(cmdarg, 0, "command not found");
	free(envpath);
	return (cmdpath);
}
