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
	int		token;
}	t_parse;

typedef	struct	s_mini{
	t_env	*env;
	char	*input;
	t_parse	*parsed_input;
	int		exit;
}	t_mini;


#endif
