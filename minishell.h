/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 17:37:13 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
#include	<sys/stat.h>
// Macros
# define PROMPT "minishell--> "
# define WHITESPACES " \t\n\r\v\f"
# define STOPS " \t\n\r\v\f><|"
# define CASES "|<>"
# define FILE_OP "\003\004\005"
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIRECT_IN 3	
# define TOKEN_REDIRECT_OUT 4
# define TOKEN_APPEND 5
# define TOKEN_HEREDOC 6
# define TOKEN_FILENAME 7
# define TOKEN_DELIMITER 8
# define SYNTAX_ERR "minishell: syntax error: invalid or unexpected input"
# define ERR_NEAR_TOKEN "\002\003\004\005\006"
# define RED "\003\004\005\006"
# define ISVAL1 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_?"
# define ISVAL2 "0123456789"


// Structs //
/* for toknization */
typedef struct s_tokens
{
	struct s_tokens			*prev;
	char					*string;
	int						flag;
	struct s_tokens			*next;
}							t_tokens;
typedef struct s_split
{
	char					*string;
	char					*map;
	struct s_split			*next;
}							t_split;
/* struct for rediraction */
typedef struct s_rediraction
{
	struct s_rediraction	*prev;
	char					*token;
	int						type;
	int                   fd;
	int						ambiguous;
	struct s_rediraction	*next;
}							t_rediraction;
// this struct for helping me extract paths
///////////////
///////////////
///////////////////
/* final struct */
typedef struct s_list
{
	struct s_list			*prev;
	char					**cmds;
    int             pid;
    char            **paths;
    char            *path;
	t_rediraction			*rediraction;
	
	struct s_list			*next;
}		
					t_list;
/* garbge collector */
typedef struct s_gc
{
	void					*ptr;
	struct s_gc				*next;
}							t_gc;
/* for env list */
typedef struct s_env
{
	char					*s;
	char			*key;
	char			*value;
	int				exported; 
	struct s_env			*next;
}							t_env;
/* info struct */
typedef struct s_info
{
	t_env					*env;
	int exit_status;
}							t_info;
/*
// Prototypes
t_info						*static_info(void);
t_env						*arr_list(char **env);
t_list						*input_analysis(char *line);
int							ft_strlen(char *s);
int							ft_strncmp(char *s1, char *s2, int n);
char						*ft_substr(char *s, int len);
char						*ft_strchr(char *s, int c);
int							check_input(char *line);
t_tokens					*split_and_store(char *line);
void						free_tokens(t_tokens *tokens);
t_tokens					*variable_expansion(t_tokens *tokens);
t_list						*tokens_to_list(t_tokens *tokens);
void						print_command_list(t_list *list);
void						free_command_list(t_list *list);
t_gc						**static_gc(void);
void						ft_free_all(void);
int							append_gc(void *ptr);
void						*ft_malloc(size_t size);
void						ft_free(void *ptr);
void						free_tokens(t_tokens *tokens);
t_tokens					*ft_expand(t_tokens *tokens);
char						*ft_getenv(char *token, int *len);
char						*ft_strjoin(char *s1, char *s2);
char						*fill_str(int len, char c);
int							get_var_len(char *s);
int							get_len(char *s, int reset);
t_split						*split_preserve_quotes(char *s, char *map);
*/
// peer stuff
t_info						*static_info(void);
t_env						*arr_list(char **env);
t_list						*input_analysis(char *line);
int							ft_strlen(char *s);
int							ft_strncmp(char *s1, char *s2, int n);
char						*ft_substr(char *s, int len);
char						*ft_strchr(char *s, int c);
int							check_input(char *line);
t_tokens					*split_and_store(char *line);
void						free_tokens(t_tokens *tokens);
t_tokens					*variable_expansion(t_tokens *tokens);
t_list						*tokens_to_list(t_tokens *tokens);
void						print_command_list(t_list *list);
t_gc						**static_gc(void);
void						ft_free_all(void);
int							append_gc(void *ptr);
void						*ft_malloc(size_t size);
void						ft_free(void *ptr);
void						free_tokens(t_tokens *tokens);
t_tokens					*ft_expand(t_tokens *tokens);
char						*ft_getenv(char *token, int *len);
char						*ft_strjoin(char *s1, char *s2);
char						*fill_str(int len, char c);
int							get_var_len(char *s);
int							get_len(char *s, int reset);
t_split						*remove_quotes(t_split *list);
t_split						*split_and_unquotes(char *string, char *map);
void						free_command_list(t_list *list);
int    ft_heredoc(t_list *list);
void    get_variables_heredoc(char *token, char **string);
//// ddddddd
void    execute_absolute_path(t_list *exec, char **env);
void    execute_relative_path(t_list *exec, char **env);
char    **extract_paths(char **env, t_list *exec);
char    *join_by_order(char const *s1, char b_slash, char const *s2);
char **ft_split(char const *s, char c);
char    *ft_strdup(const char *s);
void    ft_putstr_fd(char *s, int fd);
void    ft_putendl_fd(char *s, int fd);
int     handle_redirections(t_list *exec);
int     heredoc(char *delimiter);
void    prepare_heredocs(t_list *exec);
void    execution(t_list *cmds);
int     check_what_to_execute(t_list *list);
void restore_std_fds(int in, int out);
int  dup_std_fds(int *in, int *out);
int	list_size(t_list *lst);
void	wait_children(pid_t *pids, int count);
void	setup_io(int prev_fd, int pipe_fd[2], int has_next);
int	prepare_pipe(t_list *cmds, int pipe_fd[2]);
int init_pids(t_list *cmds, pid_t **pids, int *prev_fd);
void	child_process(t_list *cmds, char ***env, int prev_fd, int pipe_fd[2]);
void	parent_process(int *prev_fd, t_list *cmds, int pipe_fd[2]);
int check_dir(const char *path);
void check_access_abs_path(t_list *exec);
void check_relat_path_edge_cases(t_list *exec );
char **env_to_array(t_env *env);
int	is_builtin(char *cmd);
int	run_builtin(char **cmd);
int	ft_echo(char **args);
int	ft_cd(char **args);
int	ft_pwd(void);
int	ft_exit(char **args);
int	ft_env(void);
int	ft_export(char **args);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_unset(char **args);
t_env   *find_env(t_env *env ,char *key);
char    *get_env_value(t_env *env ,char *key);
void    set_env(t_env **env ,char *key,char *value);
void    unset_env(t_env **env ,char *key);
int	ft_isalpha(int c);
// signals.c
void setup_signals_parent(void);
void setup_signals_child(void);
void setup_signals_heredoc(void);
int cmp_env_str(const char *sa, const char *sb);
void swap_ptrs(char **a, char **b);
void bubble_sort_env(char **arr, int count);
void clean_exit(int status);
#endif
