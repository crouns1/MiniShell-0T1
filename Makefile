
NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = minishell.c \
       0-env.c \
       0-ft_utils.c \
       0-ft_alloc.c \
       0-static_functions.c \
       2-check_input.c \
       3-input_analysis.c \
       4-get_tokens.c \
       5-ft_expand_utils.c \
       5-ft_expand.c \
       5-getenv.c \
       5-remove_quotes.c \
       5-split_and_unquote.c \
       6-list.c \
       print.c \
       signals.c \
       exec_relative_absolute_path.c\
       exec_path_utils.c \
       path_extraction_utils.c \
       check_wht_to_execute.c \
       child_parent.c \
       init_pids.c \
       setup_io_prepare_pipe.c \
       size_of_list.c \
       wait_for_children.c \
       builtins.c \
       ft_echo.c \
       ft_cd.c \
       ft_pwd.c \
       ft_env.c \
       ft_exit.c \
       ft_export.c \
       ft_unset.c \
       utils.c \
       ft_split.c \
       execution.c \
       red_in_out.c \
       1-heredoc_expantion.c \
       1-ft_heredoc.c 

OBJS = $(SRCS:.c=.o)

INCLUDES = -I include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:
	@rm -fv $(OBJS)

fclean: clean
	@rm -fv $(NAME)

re: fclean all
