/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:14:17 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/19 23:29:36 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void sigint_parent(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    static_info()->exit_status = 130;
}

static void sigint_child(int signo)
{
    (void)signo;
    signal(SIGINT , SIG_DFL);
}

static void sigquit_child(int signo)
{
    (void)signo;
    signal(SIGQUIT , SIG_DFL);
}

static void sigint_heredoc(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    close(STDIN_FILENO); 
    static_info()->exit_status = 130;
}


void setup_signals_parent(void)
{
    signal(SIGINT, sigint_parent);
    signal(SIGQUIT, SIG_IGN);
}

void setup_signals_child(void)
{
    signal(SIGINT, sigint_child);
    signal(SIGQUIT, sigquit_child);
}

void setup_signals_heredoc(void)
{
    signal(SIGINT, sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
