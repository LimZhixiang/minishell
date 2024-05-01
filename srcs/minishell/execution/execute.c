#include "../../../includes/minishell.h"

int		cmd_word_count(t_parse *input)
{
	t_parse	*temp;
	int		word;

	word = 0;
	temp = input;
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			word++;
		temp = temp->next;
	}
	return (word);
}

char	**get_command(t_parse *input)
{
	char	**ret;
	t_parse *temp;
	int		i;

	temp = input;
	i = 0;
	ret = malloc(sizeof(char *) * (cmd_word_count(input) + 1));
	if (!ret)
		return (NULL);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type <= ARG)
			ret[i++] = ft_strdup(temp->arg);
		temp = temp->next;
	}
	ret[cmd_word_count(input)] = NULL;
	return(ret);
}

void	execute(t_mini *mini, char **envp)
{
	char	*envpath;
	char	*cmdpath;
	char	**cmdarg;

	envpath = extract_path(envp);
	cmdarg =  get_command(mini->input);
	cmdpath = getcmdpath(cmdarg[0], envpath);
	free(envpath);
	if (execve(cmdpath, cmdarg, envp) == -1)
	{
		free(cmdpath);
		free_str_arr(cmdarg);
		// error_checker(3);
	}
}

void	axe_swing(t_mini *mini, char **envp)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		return ;
	pid = fork();
	// if (pid == -1)
		// error_checker(1);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execute(mini, envp);
	}
	else
	{
		close(fds[1]);
		wait(NULL);
		print_file(fds[0]);
		close(fds[0]);
	}
}

void	chop_blk(t_mini *mini, t_parse *node, char **env)
{
	fd_handler(mini, node);
	if (mini->in != -1)
		dup2(mini->in, 0);
	if (mini->out != -1)
		dup2(mini->out, 1);
	axe_swing(mini, env);
	dup2(mini->term_in, 0);
	dup2(mini->term_out, 1);
	mini->in = -1;
	mini->out = -1;
}