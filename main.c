
#include "minishell.h"

int	get_env(t_mini *mini, char **env)
{
	t_env	*mini_env;
	t_env	*new;
	int		i;

	if (!(mini_env = malloc(sizeof(t_env))))
		return (1);
	mini_env->value = ft_strdup(env[0]);
	mini_env->next = NULL;
	mini->env = mini_env;
	i = 1;
	while (env[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->value = ft_strdup(env[i]);
		new->next = NULL;
		mini_env->next = new;
		mini_env = mini_env->next;
		i++;
	}
	return (0);
}

void	print_env(t_mini *mini)
{
	while (mini->env)
	{
		printf("%s\n", mini->env->value);
		mini->env = mini->env->next;
	}
}

int	check_quotes(char *input)
{
	int	i;
	int quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		if(quote == 0 && input[i] == '\'')
			quote = 1;
		if(quote == 0 && input[i] == '\"')
			quote = 2;
		if(quote == 1 && input[i] == '\'')
			quote = 0;
		if(quote == 2 && input[i] == '\"')
			quote = 0;
	}
	return (quote);
}

int	ft_quotes(char c, int quote)
{
	if (c)
	{
		if(quote == 0 && c == '\'')
			quote = 1;
		else if(quote == 0 && c == '\"')
			quote = 2;
		else if(quote == 1 && c == '\'')
			quote = 0;
		else if(quote == 2 && c == '\"')
			quote = 0;
	}
	return (quote);
}

int is_sep(char i)
{
	if (i == ' ')
		return(1);
	if (i == '|' || i == '>' || i == '<')
		return(0);
	return (0);
}

int	ft_arg_len(char *input, int i)
{
	int	quotes;
	int	len;

	quotes = 0;
	len = 0;
	while (input[i] && is_sep(input[i]) != 1)
	{
		if (ft_quotes(input[i], quotes) != 0)
		{
			quotes = ft_quotes(input[i], quotes);
			while(ft_quotes(input[++i], quotes) != 0)
				len++;
			quotes = ft_quotes(input[i], quotes);
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return(len);
}

void	break_arg(char *input)
{
	int i;
	int	j;
	int len;
	t_parse *new;
	int	quotes;

	i = 0;
	quotes = 0;
	while (input[i])
	{
		while(is_sep(input[i]) == 1)
			i++;
		len = ft_arg_len(input, i);
		if (len != 0)
		{
			j = 0;
			new = malloc(sizeof(t_parse));
			new->arg = malloc(sizeof(char) * len);
			while (input[i] && is_sep(input[i]) != 1)
			{
				if (ft_quotes(input[i], quotes) != 0)
				{
					quotes = ft_quotes(input[i], quotes);
					while(ft_quotes(input[++i], quotes) != 0)
						new->arg[j++] = input[i];
					quotes = ft_quotes(input[i], quotes);
					i++;
				}
				else
				{
					new->arg[j++] = input[i++];
				}
			}
		}

	}
}

void	parsing( char *input)
{
	if(check_quotes(input) != 0)
	{
		printf("nvr close quote");
	}
	break_arg(input);
}

int main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	(void)argc;
	(void)argv;
	char	hi[16] = "\"\'fdf\".h |";

	mini = malloc(sizeof(t_mini));
	get_env(mini, envp);
	parsing(hi);
}
// 1. readline()
// 	library: <readline/readline.h>
// 	Inputs: readline("prompt message")
// 	Outputs: char*

// 2. rl_add_history()
// 	library: <readline/history.h>
// 	Input: rl_clear_history(char *)
// 	Output: Nil
// 	Purpose: Used to add the inputs entered bby the users into a struct

// 3. rl_clear_history()
// 	library: <readline/history.h>
// 	Input: rl_clear_history(nil)
// 	Outputs: Nil
// 	Purpose: Clears inputs history that is keyed by user when using readline and stored into rl_add_history.

// 4. rl_on_new_line()
// 	library: <readline/history.h>