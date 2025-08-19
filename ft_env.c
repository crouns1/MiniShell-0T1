/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/20 00:19:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(void)
{
    t_env *env = static_info()->env;
    while (env)
    {
        printf("%s\n", env->s);
        env = env->next;
        // if(env->next) {
            // ft_putendl_fd("args not on point " , 2);
        // }
    }
    return 0;
}
