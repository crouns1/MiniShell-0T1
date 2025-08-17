/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/17 21:01:55 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    history(char *line)
{
    if (!line || !*line)
        return ;
    add_history(line);
}

void    initialise_info(char **env)
{
    t_info  *info;

    info = static_info();
    info->env = arr_list(env);
    info->exit_status = 0;
}

static void shell_loop(char **env)
{
    char    *line;
    t_list  *list;
    while (1)
    {
        line = readline(PROMPT);
        if(!line) {
            write(1,"exit\n",5);
            exit(0);
        }
        history(line);
        if (check_input(line))
            continue ;
        list = input_analysis(line);
        if (!list)
        {
            static_info()->exit_status = 2;
            continue ;
        }
        prepare_heredocs(list);
        if (!check_what_to_execute(list, &env))
            execution(list, env);
        // print_command_list(list);
        // free_command_list(list);
    }
}

int     main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    initialise_info(env);
    signals();
    shell_loop(env);
    return (0);
}

