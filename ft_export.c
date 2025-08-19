/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:13:33 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/20 00:22:32 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


// jait-chd@c1r3p11:~$ export a=adasdaa  5=dasada =
// bash: export: `5=dasada': not a valid identifier
// bash: export: `=': not a valid identifier
// jait-chd@c1r3p11:~$ 

int ft_export(char **args)
{
    int i = 1;

    if (!args[i])
    {
        t_env *env = static_info()->env;
        while (env)
        {
            printf("declare -x %s\n", env->s);
            env = env->next;
        }
        return 0;
    }
    while (args[i])
    {
        char *eq = ft_strchr(args[i], '=');
        if (eq)
        {
            *eq = '\0';
            set_env(&static_info()->env, args[i], eq + 1);
        }
        else
            set_env(&static_info()->env, args[i], "");
        i++;
    }
    return 0;
}
