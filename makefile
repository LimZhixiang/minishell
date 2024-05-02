NAME = minishell

MINISHELL_DIR = srcs/minishell/

BUILT_INS_DIR = $(MINISHELL_DIR)/built_ins/
ENV_DIR = $(MINISHELL_DIR)env/
PARSING_DIR = $(MINISHELL_DIR)parsing/
SIGNAL_DIR = $(MINISHELL_DIR)signal/
REDIR_DIR = $(MINISHELL_DIR)redir/
EXECUTE_DIR = $(MINISHELL_DIR)execution/
UTILS_DIR = $(MINISHELL_DIR)utils/

SRC_FILES = \
	main.c

PARSING_FILES = \
	parsing_main.c parsing_rm_quote.c parsing_token_utils.c \
	parsing_token.c parsing_helpers.c

SIGNAL_FILES = \
	signal.c

ENV_FILES = \
	env.c get_env_arr.c

REDIR_FILES = \
	fd_handler.c heredoc.c

EXECUTE_FILES = \
	execute.c cmdpath.c

UTILS_FILES = \
	pipe_present.c print_file.c print_cmd_error.c

#Libft files
LIBFT = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_atol.c ft_strcmp.c ft_atoi_base.c \
	free_str_arr.c ft_isspace.c str_isdigit.c str_find_replace.c find_word.c \
	get_next_line.c

LIBFTBONUS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

#files that manipulates env in user input
SRC = $(addprefix $(MINISHELL_DIR), $(SRC_FILES))
ENV = $(addprefix $(ENV_DIR), $(ENV_FILES))
PARSING = $(addprefix $(PARSING_DIR), $(PARSING_FILES))
SIGNAL = $(addprefix $(SIGNAL_DIR), $(SIGNAL_FILES))
REDIR = $(addprefix $(REDIR_DIR), $(REDIR_FILES))
BUILT_INS= $(addprefix srcs/minishell/built_ins/env/, $(ENV_FUNC))
EXECUTE= $(addprefix $(EXECUTE_DIR), $(EXECUTE_FILES))
UTILS= $(addprefix $(UTILS_DIR), $(UTILS_FILES))

#files that check env in user input
ENV_FUNC = input_env_check.c input_env_utils.c input_env.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -lncurses

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(addprefix srcs/libft/, $(LIBFT)) $(ENV) $(PARSING) $(SIGNAL) $(REDIR) $(BUILT_INS) $(EXECUTE) $(UTILS) $(LFLAGS)

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
