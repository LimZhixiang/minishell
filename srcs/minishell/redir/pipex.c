#include "../../../includes/minishell.h"

void	pipex(t_mini *mini, t_parse *node, char **envp)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (pipe(fds) == -1)
		return ;
	pid = fork();
	// if (pid == -1)
	// 	error_checker(1);
	if (pid == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		execute(mini, node, envp);
	}
	else
	{
		dup2(fds[0], 0);
		close(fds[1]);
		if (mini->pipe == 0)
		{
			dup2(mini->term_out, 1);
			print_file(fds[0]);
		}
		close(fds[0]);
		wait(&status);
	}
	mini->status = WEXITSTATUS(status);
}

void	pipe_handler(t_mini *mini, t_parse *node, char **envp)
{
	if (mini->in != -1)
		dup2(mini->in, 0);
	if (mini->out != -1)
		dup2(mini->out, 1);
	pipex(mini, node,envp);
}