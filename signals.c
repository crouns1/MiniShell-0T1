/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:14:17 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/18 23:45:24 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// ============= HANDLERS =============

// For interactive shell (prompt)
static void sigint_parent(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    static_info()->exit_status = 130;
}

static void sigquit_parent(int signo)
{
    (void)signo;
    // Ignore Ctrl-\ in prompt
    rl_on_new_line();
    rl_redisplay();
}

// For child processes
static void sigint_child(int signo)
{
    (void)signo;
    write(1, "\n", 1);
}

static void sigquit_child(int signo)
{
    (void)signo;
    write(1, "Quit: 3\n", 8);
}

// For heredoc reader
static void sigint_heredoc(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    close(STDIN_FILENO); // force readline to return NULL
    static_info()->exit_status = 130;
}

// ============= SETUP API =============

void setup_signals_parent(void)
{
    signal(SIGINT, sigint_parent);
    signal(SIGQUIT, sigquit_parent);
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
