#ifndef MINISHELL_H
# define MINISHELL_H

# define CMD	1
# define ARG 2
# define DELIMITER 3
# define FILENAME 4
# define PIPE 5
//>,>>
# define OUTPUT 6
# define APPEND 7
//<, <<
# define INPUT 8
# define HDOC 9

# include <sys/types.h>
# include <sys/wait.h>
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
# include <errno.h>
# include "../srcs/libft/libft.h"

//Input checkers
int		env_found(char *line);
char	*invalid_env(char *line);

//Input env manipulation
char	*convert_env(char *line, char **envp);
char	*replace_env(char *line, char *envp, char *envp_name, int index);
int		find_env(char *line, char *wrd);
char	*get_envp_name(char *str);
char	*get_envp_value(char *str);

typedef struct s_env{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_parse{
	char			*arg;
	int				type;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

typedef struct s_mini{
	t_env	*env;
	t_parse	*input;
	int		in;
	int		out;
	int		term_in;
	int		term_out;
	int		status;
	int		pipe;
	int		exit;
}	t_mini;

//parsing
//parsing_main.c
char	*ft_var_exp(char *new, t_mini *mini);
int		ft_space_line(char *new, char *line);
char	*ft_alloc_space(char *line);
int		parsing(char *line, t_mini *mini);

//parsing_rm_quotes.c
void	cpy_rm_quote(char *result, char *current);
int		rm_quote_letters(char *new);
char	*rm_node_quote(char *current);
void	ft_rm_quotes(t_mini *mini);

//parsing_token.c
void	ft_copy_letters(char *ret, char *new, int i);
char	*mini_cpy_letters(char *new, int i);
char	**ft_mini_split(char *new);
void	check_syntax(t_mini *mini);
void	tokenization(char *new, t_mini *mini);

//parsing_token_helpers.c
int		operator_type(t_parse *node, int *CMD_FLAG);
int		wrd_count(char *new);
int		mini_letters(char *new, int i, int flag);
t_parse	*ft_newnode(char *content, t_parse *prev);

//./helpers.c
int		is_sep(char c);
int		ft_quote_c(char c);
int		ft_quote(char *line, int i);

//./env/get_env.c
int		init_mini_env(t_mini *mini, char **env);
int		env_compare(char *env, char *name);
char	*ft_get_env(char *name, t_mini *mini);
char	*replace_env(char *line, char *envp, char *envp_name, int index);
int		ft_valid_env(char c);

int		env_node_count(t_env *env);
char	**get_env_arr(t_mini *mini);

//./redir/
void	fd_handler(t_mini *mini, t_parse *head);
void	filehandler(char *filename, int *fd, int flag);
void	heredoc(t_mini *mini, char *eof);
void	pipex(t_mini *mini, t_parse *node, char **envp);
void	pipe_handler(t_mini *mini, t_parse *node, char **envp);

//./execution/cmdpaths.c
char	*extract_path(char **env);
char	*check_cmd(char *envpath, char *cmd);
char	*getcmdpath(char *cmdarg, char *envpath);

//./execution/execute.c
int		cmd_word_count(t_parse *input);
char	**get_command(t_parse *input);
void	execute(t_mini *mini, t_parse *node, char **envp);
void	exec_handler(t_mini *mini, t_parse *node, char **env);

//./signal/signal.c
void	signal_controller(void);

//./utils
int		pipe_present(t_parse *head);
void	print_file(int fd);
void	print_cmd_error(char *cmd, char *str);

#endif
