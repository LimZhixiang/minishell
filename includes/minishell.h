/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CMD 1
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

# define RE_SHELL 1
# define EXIT_SHELL 2

# define PATH_MAX 4096

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <term.h>
# include <termios.h>
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

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_parse
{
	char			*arg;
	int				type;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

typedef struct s_mini
{
	t_env	*env;
	t_parse	*input;
	char	*user_input;
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
char	*ft_var_exp(char *arg, t_mini *mini, int flag);
int		ft_space_line(char *new, char *line);
char	*ft_alloc_space(char *line);
int		parsing(char *line, t_mini *mini);
void	ft_free_all(t_mini *mini, int state);

//parsing_rm_quotes.c
void	cpy_rm_quote(char *result, char *current);
int		rm_quote_letters(char *new);
char	*rm_node_quote(char *current);
void	ft_rm_quotes(t_mini *mini);

//parsing_token.c
void	ft_copy_letters(char *ret, char *new, int i);
char	*mini_cpy_letters(char *new, int i);
char	**ft_mini_split(char *new);
int		check_syntax(t_mini *mini);
int		tokenization(t_parse *node, int *CMD_FLAG);

//parsing_token_helpers.c
int		wrd_count(char *new);
int		mini_letters(char *new, int i, int flag);
t_parse	*ft_newnode(char *content, t_parse *prev);

//./helpers.c
int		is_sep(char c);
int		ft_quote_c(char c);
int		ft_quote(char *line, int i);
char	*get_line_env(char *line, t_mini *mini, int i, int j);
char	*get_status_code(char *line, t_mini *mini, int i);

//./env/get_env.c
int		init_mini_env(t_mini *mini, char **env);
int		env_compare(char *env, char *name);
char	*ft_get_env(char *name, t_mini *mini);
char	*replace_env(char *line, char *envp, char *envp_name, int index);
int		ft_valid_env(char c);

int		env_node_count(t_env *env);
char	**get_env_arr(t_mini *mini);

//./redir/
int		fd_handler(t_mini *mini, t_parse *head);
int		filehandler(char *filename, int *fd, int flag);
void	heredoc_controller(t_mini *mini, char *eof, int fd);
void	pipe_handler(t_mini *mini, t_parse *node, char **envp);

//./execution/cmdpaths.c
char	*extract_path(char **env);
char	*check_cmd(char *envpath, char *cmd);
char	*getcmdpath(char *cmdarg, char *envpath);

//./execution/execute.c
char	**get_command(t_parse *input);
void	execute(t_parse *node, char **envp);
void	exec_handler(t_mini *mini, t_parse *node, char **env);

//./execution/getcmd.c
char	**get_command(t_parse *input);

//./built_ins/builtin_main.c
int		builtin_handler(t_mini *mini, t_parse *node);

//./built_ins/directory.c
int		cd_handler(t_mini *mini, char **line);
int		pwd_handler(t_mini *mini);

//./built_ins/env_builtin.c
int		env_builtin(t_mini *mini, char **cmdarg);

//./built_ins/modifyenv.c
int		export(t_mini *mini, char **cmdarg);
int		unset(t_mini *mini, char **cmdarg);

//./built_ins/builtin_exit.c
int		mini_exit(t_mini *mini, char **cmdarg);

//./signal/signal.c
void	signal_controller(void);
void	pipe_signal(pid_t pid);
int		get_signal_status(int status);

//./utils
t_parse	*nxt_subshell(t_mini *mini, t_parse *node);
int		pipe_present(t_parse *head);
void	print_file(int fd);
void	print_cmd_error(char *cmd, int code, char *str);

void	free_t_parse(t_parse *ptr);
void	print_syntax_error(char *syntax);

void	add_node(t_env *head, t_env *new);
t_env	*del_curr_node(t_env *prev, t_env *del, t_mini *mini);
t_env	*create_node(char *value);
void	replace_node(t_env *node, char *env_name, char *value);

int		init_input(char **split, t_mini *mini);
char	**ft_split_var_exp(char **split, t_mini *mini);
int		check_syntax(t_mini *mini);

int		check_quote_syntax(char *line);
int		echo_handler(t_mini *mini, char **cmdarg);
void	print_env_error(char *arg, t_mini *mini, int error_code);
void	signal_controller_2(void);

#endif
