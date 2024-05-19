#include "../../../includes/minishell.h"

void	subshell_recus(t_mini *mini, t_parse *current, int cmd, int index, int input_fd, char **env)
{
	if (index == cmd)
		return ;
	int pipefd[2];
    if (index < cmd - 1) {
        if (pipe(pipefd) == -1) {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
    }
	fd_handler(mini, current);
	pid_t pid = fork();
	if (pid == 0)
	{
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
		if (index < cmd - 1) 
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
		execute(current, env);
	}
	else
	{
		if (input_fd != -1)
			close(input_fd);
		if (index < cmd - 1)
		{
			close(pipefd[1]);
			current = nxt_subshell(mini, current);
			subshell_recus(mini, current, cmd, index + 1, pipefd[0], env);
		}
		waitpid(pid, NULL, 0);
	}
}

int	no_of_pipe(t_parse *input)
{
	int	pipe;
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
	int		num_cmd;

	tmp = mini->input;
	num_cmd = no_of_pipe(node) + 1;
	subshell_recus(mini, tmp, num_cmd, 0, -1, env);
}