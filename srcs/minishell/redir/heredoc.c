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

void	heredoc(t_mini *mini, char *eof)
{
	int		tmpfd;
	char	*line;

	(void) mini;
	tmpfd = -1;
	g_type = 2;
	filehandler(".heredoctemp.tmp", &tmpfd, OUTPUT);
	while (1)
	{
		// if (g_type != 3)
		// {
		line = readline("heredoc> ");
		// 	i++;
		// 	printf("%s,%i, %i\n", rl_prompt, i, g_type);
		// }	
		// if (g_type == 3)
		// {
		// 	break;
		// }
		if (line == 0 || ft_strcmp(line, eof))
		{
			if (line == 0)
				print_cmd_error
					("here-document got end-of-file instead of", eof);
			break ;
		}
		else
		{
			line = ft_var_exp(line, mini);
			ft_putendl_fd(line, tmpfd);
		}
		free(line);
	}
	free(line);
	close(tmpfd);
}
