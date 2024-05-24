/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:34:45 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/15 17:34:46 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	export(t_mini *mini, char *env)
{
	t_env	*new;
	char	*arg_name;
	int		status;

	status = 1;
	if (!valid_env_name(env))
	{
		print_env_error(env, mini, 1);
		return (1);
	}
	arg_name = get_envp_name(env);
	if (!arg_name)
		status = 0;
	if (is_current_env(mini, env, arg_name) == 0 && status)
	{
		new = create_node(env);
		mini->env = add_node(mini->env, new);
		if (!new)
			status = 0;
	}
	free(arg_name);
	return (1);
}
