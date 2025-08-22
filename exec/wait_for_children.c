/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:21:12 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 15:38:25 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_child_status(int status, t_info *info)
{
    int sig;

    if (WIFEXITED(status))
        info->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        sig = WTERMSIG(status);
        if (sig == SIGINT)
        {
            write(1, "\n", 1);
            info->exit_status = 130;
        }
        else if (sig == SIGQUIT)
        {
            write(1, "core dump\n", 11);
            info->exit_status = 131;
        }
    }
    else
        info->exit_status = 1;
}

void	wait_children(pid_t *pids, int count)
{
    int i;
    int status;
    t_info *info;

    info = static_info();
    i = 0;
    while (i < count)
    {
        waitpid(pids[i], &status, 0);
        if (i == count - 1)
            handle_child_status(status, info);
        i++;
    }
}
