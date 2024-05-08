/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinmain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:34:45 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:34:46 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_handler(t_mini *mini, t_parse *node)
{
	int		status;
	char	**cmdarg;

	(void) mini;
	status = 0;
	cmdarg = get_command(node);
	if (ft_strcmp(cmdarg[0], "cd"))
		status = cd_handler(mini, cmdarg);
	else if (ft_strcmp(cmdarg[0], "pwd"))
		status = pwd_handler(mini);
	else if (ft_strcmp(cmdarg[0], "echo"))
		status = echo_handler(mini, cmdarg);
	else if (ft_strcmp(cmdarg[0], "export"))
		status = export(mini, cmdarg);
	else if (ft_strcmp(cmdarg[0], "unset"))
		status = unset(mini, cmdarg);
	else if (ft_strcmp(cmdarg[0], "env"))
		status = env_builtin(mini, cmdarg);
	else if (ft_strcmp(cmdarg[0], "exit"))
		status = mini_exit(mini, cmdarg);
	free_str_arr(cmdarg);
	return (status);
}
