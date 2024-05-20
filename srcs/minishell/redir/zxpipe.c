#include "../../../includes/minishell.h"

void	subshell_child(t_mini *mini, t_parse *next, int input_fd, int *pipefd)
{
	if (mini->status != 0)
		exit(mini->status);
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (mini->in != -1)
	{
		dup2(mini->in, STDIN_FILENO);
		close(mini->in);
	}
	if (next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (mini->out != -1)
	{
		dup2(mini->out, STDOUT_FILENO);
		close(mini->out);
	}
}

int	create_pipe(t_parse *next, int *pipefd, t_mini *mini)
{
	if (next != NULL)
	{
		if (pipe(pipefd) == -1)
		{
			mini->status = 1;
			return (0);
		}
		return (1);
	}
	return (1);
}

t_pipe	subshell_var(t_parse *next_cmd, int *pipe, char **envs, int fd_input)
{
	t_pipe	ret;

	ret.next = next_cmd;
	ret.pipefd = pipe;
	ret.env = envs;
	ret.input_fd = fd_input;
	return (ret);
}

void	subshell_parent(t_pipe info, t_mini *mini)
{
	mini->status = 0;
	if (info.input_fd != -1)
		close(info.input_fd);
	if (info.next != NULL)
	{
		close(info.pipefd[1]);
		subshell_recus(mini, info.next, info.pipefd[0], info.env);
	}
}

void	subshell_recus(t_mini *mini, t_parse *current, int input_fd, char **env)
{
	int		pipefd[2];
	int		status;
	t_parse	*next;
	t_pipe	info;
	pid_t	pid;

	next = nxt_subshell(mini, current);
	info = subshell_var(next, pipefd, env, input_fd);
	if (create_pipe(next, pipefd, mini) == 0)
		return ;
	pid = fork();
	pipe_signal(pid);
	if (pid == 0)
	{	
		fd_handler(mini, current);
		if (mini->status)
			exit(mini->status);
		subshell_child(mini, next, input_fd, pipefd);
		execute(current, env);
	}
	else
	{
		// waitpid(pid, &status, 0);
		subshell_parent(info, mini);
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
			mini->status = get_signal_status(status);
		else
			mini->status = WEXITSTATUS(status);
	}
}

int	no_of_pipe(t_parse *input)
{
	int		pipe;
	t_parse	*temp;

	temp = input;
	pipe = 0;
	while (temp)
	{
		if (temp->type == PIPE)
			pipe++;
		temp = temp->next;
	}
	return (pipe);
}

void	subshell2(t_mini *mini, t_parse *node, char **env)
{
	t_parse	*tmp;

	tmp = mini->input;
	tmp = node;
	subshell_recus(mini, tmp, -1, env);
}
