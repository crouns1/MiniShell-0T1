/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/18 06:37:03 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int    global_e(int status)
{
    static int value;
    if (status == -1)
        return (value);
    value = status;
    return(value);
}
int    global_e(int status)
{
    static int value;
    if (status == -1)
        return (value);
    value = status;
    return(value);
}*/

void sighand()
{
    write(1, "\n", 1);
    ft_free_all();
    exit(130);
}
int heredoc(char *delimiter)
{
    char    *line;
    int fds;
    int e = 0;
    pid_t pid;
    
    fds = open("text.txt", O_CREAT | O_RDWR, 0644);
    
    pid = fork();
    if (pid == -1)
        perror("Error");
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        while (1)
        {
            signal(SIGINT, sighand);
            line = readline("> ");
            if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
            {
                free(line);
                break ;
            }
            write(fds, line, ft_strlen(line));
            write(fds, "\n", 1);
            free(line);
        }
        exit(0);
    }
    signal(SIGINT, SIG_IGN);
    close(fds);
    waitpid(pid , &e , 0);
    if (WIFEXITED(e))
    {
        static_info()->exit_status = WEXITSTATUS(e);
    }
    else if (WIFSIGNALED(e))
        static_info()->exit_status = WTERMSIG(e) + 128;
    printf("%d", static_info()->exit_status);
    fds = open("text.txt", O_RDWR);
    unlink("text.txt");
    return (fds);
}

void    prepare_heredocs(t_list *exec)
{
    t_rediraction   *r;

    while (exec)
    {
        r = exec->rediraction;
        while (r)
        {
            if (r->type == TOKEN_HEREDOC)
                r->fd = heredoc(r->token);
            r = r->next;
        }
        exec = exec->next;
    }
}

