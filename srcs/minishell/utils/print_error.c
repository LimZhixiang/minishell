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

void	print_env_error(char *arg, t_mini *mini, int error_code)
{
	mini->status = error_code;
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	print_syntax_error(char *syntax)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(syntax, 2);
	ft_putstr_fd("\n", 2);
}

void	print_cmd_error(char *cmd, int code, char *str)
{
	if (*cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (code)
	{
		ft_putstr_fd(strerror(code), 2);
		if (*str)
			ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

// void	print_cmd_error(char *cmd, char *str)
// {
// 	if (*cmd)
// 	{
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": ", 2);
// 	}
// 	if (errno)
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		if (*str)
// 			ft_putstr_fd(": ", 2);
// 	}
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd("\n", 2);
// }