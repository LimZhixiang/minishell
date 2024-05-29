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

static void	interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_controller(void)
{
	signal(SIGINT, interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	pipe_signal(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	get_signal_status(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == 2)
	{
		write(2, "\n", 2);
		rl_redisplay();
		return (130);
	}
	else if (sig == 3)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (131);
	}
	return (0);
}
