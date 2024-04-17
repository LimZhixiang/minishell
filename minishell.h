# ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <term.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

//Input checkers
int	env_found(char *line);
char	*invalid_env(char *line);

//Input env manipulation
char	*convert_env(char *line, char **envp);
char	*replace_env(char *line, char *envp, char *envp_name, int index);
int	find_env(char *line, char *wrd);
char	*get_envp_name(char *str);
char	*get_envp_value(char *str);

typedef	struct	s_env{
	char			*value;
	struct	s_env	*next;
}	t_env;

typedef struct	s_parse{
	char	*arg;
	int		type;
	struct s_parse	*next;
}	t_parse;

typedef	struct	s_mini{
	t_env	*env;
	char	*in;
	t_parse	*input;
	int		exit;
}	t_mini;

//parsing
//parsing_main.c
char	*ft_var_exp(char *new, t_mini *mini);
int		ft_space_line(char *new, char *line);
char	*ft_alloc_space(char *line);
int		parsing(char *line, t_mini *mini);
//parsing_minisplit.c
void	ft_copy_letters(char *ret, char *new, int i);
char	*mini_cpy_letters(char *new, int i);
char	**ft_mini_split(char *new);
void	input_init(char *new, t_mini *mini);
//parsing_split_helpers.c
int	wrd_count(char *new);
int	mini_letters(char *new, int i, int flag);
t_parse	*ft_newnode(char *content);

//./helpers.c
int	is_sep(char c);
int	ft_quote_c(char c);
int	ft_quote(char *line, int i);

//./env/get_env.c
int	mini_env(t_mini *mini, char **env);
int	env_compare(char *env, char *name);
char	*ft_get_env(char *name, t_mini *mini);
char	*replace_env(char *line, char *envp, char *envp_name, int index);
int	ft_valid_env(char c);


















#endif
