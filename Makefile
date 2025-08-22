
NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = minishell.c \
       print.c\
       parse/0-env.c \
       parse/0-ft_utils.c \
       parse/0-ft_alloc.c \
       parse/0-static_functions.c \
       parse/2-check_input.c \
       parse/3-input_analysis.c \
       parse/4-get_tokens.c \
       parse/5-ft_expand_utils.c \
       parse/5-ft_expand.c \
       parse/5-getenv.c \
       parse/5-remove_quotes.c \
       parse/5-split_and_unquote.c \
       parse/6-list.c \
       exec/signals.c \
       exec/exec_relative_absolute_path.c\
       exec/exec_path_utils.c \
       exec/path_extraction_utils.c \
       exec/check_wht_to_execute.c \
       exec/child_parent.c \
       exec/init_pids.c \
       exec/setup_io_prepare_pipe.c \
       exec/size_of_list.c \
       exec/wait_for_children.c \
       builtins/builtins.c \
       builtins/ft_echo.c \
       builtins/ft_cd.c \
       builtins/ft_pwd.c \
       builtins/ft_env.c \
       builtins/ft_exit.c \
       builtins/ft_export.c \
       builtins/ft_unset.c \
       builtins/builtins_help.c \
       builtins/builtins_help2.c \
       builtins/set_unset_var.c \
       exec/utils.c \
       exec/ft_split.c \
       exec/execution.c \
       exec/red_in_out.c \
       exec/1-heredoc_expantion.c \
       exec/1-ft_heredoc.c 

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
