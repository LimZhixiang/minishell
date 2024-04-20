NAME = minishell

SRC = \
	main.c helpers.c

PARSING = \
	parsing_main.c parsing_minisplit.c parsing_split_helpers.c

SIGNAL = \
	signal.c
ENV = \
	env.c

#Libft files
LIBFT = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_atol.c ft_strcmp.c ft_atoi_base.c \
	free_str_arr.c ft_isspace.c str_isdigit.c str_find_replace.c find_word.c

LIBFTBONUS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

#files that manipulates env in user input
INPUT_MANIPULATION= input_env_utils.c input_env.c

#files that check env in user input
INPUT_CHECK = input_env_check.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -lncurses

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(addprefix libft/, $(LIBFT)) $(addprefix signal/, $(SIGNAL)) $(addprefix parsing/, $(PARSING)) $(addprefix env/, $(ENV)) $(INPUT_CHECK) $(INPUT_MANIPULATION) $(LFLAGS)

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
