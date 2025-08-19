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

void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
    write(2, "Quit (core dumped)\n", 19);
}

void sig_int(void)
{
   signal(SIGINT , handle_sigint);
}

void sig_quit(void)
{
   
    signal(SIGQUIT , SIG_IGN);
}


void signals(void)
{
    sig_int();
    sig_quit();
}
