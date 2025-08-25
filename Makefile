.PHONY: all clean fclean re

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

SRCS        =   minishell.c\
		builtins/builtins_help.c\
		builtins/builtins_help2.c\
		builtins/ft_pwd.c\
		builtins/ft_env.c\
		builtins/ft_exit.c\
		builtins/ft_cd.c\
		builtins/builtins.c\
		builtins/set_unset_var.c\
		builtins/ft_export.c\
		builtins/ft_unset.c\
		builtins/ft_echo.c\
		exec/setup_io_prepare_pipe.c\
		exec/exec_path_utils.c\
		exec/size_of_list.c\
		exec/red_in_out.c\
		exec/utils.c\
		exec/init_pids.c\
		exec/1-ft_heredoc.c\
		exec/1-heredoc_utils.c\
		exec/1-heredoc_expantion.c\
		exec/ft_split.c\
		exec/exec_relative_absolute_path.c\
		exec/child_parent.c\
		exec/wait_for_children.c\
		exec/signals.c\
		exec/execution.c\
		exec/check_wht_to_execute.c\
		exec/path_extraction_utils.c\
		parser/0-ft_alloc.c\
		parser/5-list.c\
		parser/4-ft_expand.c\
		parser/0-static_functions.c\
		parser/0-env.c\
		parser/4-split_and_unquote.c\
		parser/4-ft_expand_utils.c\
		parser/0-ft_utils.c\
		parser/2-input_analysis.c\
		parser/4-getenv.c\
		parser/4-remove_quotes.c\
		parser/4-get_expand.c\
		parser/3-get_tokens.c\
		parser/1-check_input.c\


OBJDIR      = obj
OBJS        = $(SRCS:%.c=$(OBJDIR)/%.o)

RM          = rm -f
RMDIR       = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)/$(dir $<)
	$(CC) $(CFLAGS) -c $< -o $(notdir $@)
	@mv $(notdir $@) $@

clean:
	$(RMDIR) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
