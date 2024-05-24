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

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
}	t_export;

typedef struct s_parse
{
	char			*arg;
	int				type;
	char			*heredoc;
	int				heredoc_fd;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

typedef struct s_pipe
{
	char	**env;
	t_parse	*next;
	int		fd_status;
	int		*pipefd;
	int		input_fd;
	int		*status;
}	t_pipe;

typedef struct s_mini
{
	t_env		*env;
	t_parse		*input;
	t_export	*list;
	char		*user_input;
	int			in;
	int			out;
	int			term_in;
	int			term_out;
	int			std_err;
	int			status;
	int			pipe;
	int			exit;
}	t_mini;

//start
//./built_ins/env/input_env_check.c
int			env_found(char *line);
char		*invalid_env(char *line);
//./built_ins/env/input_env_utils.c
int			find_env(char *line, char *wrd);
char		*get_envp_name(char *str);
char		*get_envp_value(char *str);

//./built_ins/builtin_exit.c
int			mini_exit(t_mini *mini, char **cmdarg);
//./built_ins/main.c
int			builtin_handler(t_mini *mini, t_parse *node);
//./built_ins/directory.c
int			cd_handler(t_mini *mini, char **line);
int			pwd_handler(t_mini *mini);
//./built_ins/echo.c
int			echo_handler(t_mini *mini, char **cmdarg);
//./built_ins/env_builtin.c
int			env_builtin(t_mini *mini, char **cmdarg);
//./built_ins/env_modify_env.c
int			export_handler(t_mini *mini, char **cmdarg);
int			export(t_mini *mini, char *env);
int			unset(t_mini *mini, char **cmdarg);
int			valid_env_name(char *line);
int			is_current_env(t_mini *mini, char *arg, char *arg_name);

//./env/env.c
int			init_mini_env(t_mini *mini, char **env);
int			env_compare(char *env, char *name);
char		*ft_get_env(char *name, t_mini *mini);
char		*replace_env(char *line, char *envp, char *envp_name, int index);
//./env/get_env_arr
char		**get_env_arr(t_mini *mini);

//./execution/cmdpath
char		*extract_path(char **env);
char		*getcmdpath(char *cmdarg, char *envpath);
//./execution/execute.c
void		execute(t_parse *node, char **envp);
void		exec_handler(t_mini *mini, t_parse *node, char **env);
//./execution/getcmd.c
char		**get_command(t_parse *input);

//./parsing/helpers.c
int			is_sep(char c);
int			ft_quote_c(char c);
int			ft_quote(char *line, int i);
int			ft_valid_env(char c);
//./parsing/parsing_init_input.c
int			init_input(char **split, t_mini *mini);
//./parsing/parsing_main.c
int			parsing(char *line, t_mini *mini);
//./parsing/parsing_mini_split.c
char		**ft_mini_split(char *new);
//./parsing/parsing_rm_quotes.c
void		ft_rm_quotes(t_mini *mini);
//./parsing/parsing_syntax_check.c
int			check_syntax(t_mini *mini);
int			check_quote_syntax(char *line);
//./parsing/parsing_tokenization.c
int			tokenization(t_parse *node, int *CMD_FLAG);
//./parsing/parsing_var_exp.c
char		*get_status_code(char *line, t_mini *mini, int i);
char		*get_line_env(char *line, t_mini *mini, int i, int j);
char		*ft_var_exp(char *arg, t_mini *mini, int flag);

int			export_exist(t_mini *mini, char *name);
void		export_list(t_mini *mini, char *env);
void		print_export_lst(t_mini *mini);
void		rplace_export_value(t_mini *mini, char *arg, char *arg_name);
t_export	*rmv_list(t_export *list, char *name);

//./built_ins/builtin_exit.c
int			mini_exit(t_mini *mini, char **cmdarg);
//./redir/fd_handler.c
int			filehandler(char *filename, int *fd, int flag);
int			fd_handler(t_mini *mini, t_parse *head);
//./redir/heredoc_handler.c
int			heredoc_handler(t_mini *mini);
//./redir/heredoc.c
void		heredoc_controller(t_mini *mini, char *eof, int fd);
//./redir/pipex.c
int			subshell_recus(t_mini *mini, t_parse *current, int input_fd,
				char **env);

//./signal/signal.c
void		signal_controller(void);
void		pipe_signal(pid_t pid);
int			get_signal_status(int status);

//./utils/env_node_utils.c
t_env		*add_node(t_env *head, t_env *new);
void		replace_node(t_env *node, char *env_name, char *value);
t_env		*create_node(char *value);
t_env		*del_curr_node(t_env *prev, t_env *del, t_mini *mini);

void		ft_free_all(t_mini *mini, int state);

t_export	*add_export_node(t_export *head, t_export *new);
void		replace_export_node(t_export *node, char *env_name, char *value);
t_export	*create_export_node(char *name, char *value);
t_export	*del_export_node(t_export *prev, t_export *del);

char		*here_doc_exp(char *arg, t_mini *mini);

int			is_direct(char *path);
void		print_env_error(char *arg, t_mini *mini, int error_code);
void		print_syntax_error(char *syntax);
void		print_cmd_error(char *cmd, int code, char *str);
int			str_empty(char *str);
int			pipe_present(t_parse *head);
int			create_pipe(t_parse *next, int *pipefd, t_mini *mini);
t_pipe		subshell_var(t_parse *next, int *pipe, char **envs, int fd_input);
t_parse		*nxt_subshell(t_mini *mini, t_parse *node);

void		print_error_file(t_mini *mini);
void		create_error_file(t_parse *current);

//end

#endif
