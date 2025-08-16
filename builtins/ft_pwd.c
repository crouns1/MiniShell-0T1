/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:23 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
/*
int ft_pwd(char **args)
{
        char cwd[1024];

        if (args[1] && args[1][0] == '-' && args[1][1])
                return (write(2, "minishell: pwd: invalid option\n", 31), 1);
        if (!getcwd(cwd, sizeof(cwd)))
                return (perror("pwd"), 1);
        write(1, cwd, strlen(cwd));
        write(1, "\n", 1);
        return (0);
}*/

#include <errno.h>
#include <string.h>

/* If you have your own env getter, replace getenv("PWD") with ms_getenv("PWD") */
int ft_pwd(char **args)
{
    char cwd[1024];

    if (args[1] && args[1][0] == '-' && args[1][1])
        return (write(2, "minishell: pwd: invalid option\n", 31), 1);

    if (!getcwd(cwd, sizeof(cwd))) {
        /* Only special-case “directory vanished / inaccessible” */
        if (errno == ENOENT || errno == EACCES) {
            const char *lpwd = getenv("PWD"); /* or ms_getenv("PWD") */
            if (lpwd && *lpwd) {
                write(1, lpwd, strlen(lpwd));
                write(1, "\n", 1);
                return 0;
            }
        }
        /* Otherwise keep your original behavior */
        perror("pwd");
        return 1;
    }

    write(1, cwd, strlen(cwd));
    write(1, "\n", 1);
    return 0;
}

