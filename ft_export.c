/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:13:33 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/20 06:56:32 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #define SYMBOLS "! \" # $ % & ' ( ) * + , - .
// 	/ : ; < = > ? @ [ \\ ] ^ ` { | } ~"

// void ft_sort(t_env *env) {
//     char c;
//     while(env->s) {
//         while(env->next) {
//             if(env > env->next) {
//                 c = env;
//                 env = env->next;
//                 env->next = c;
//             }
//         }
//     }
// }


// void ft_sort(char **args) {
//     int i = 0;
//     int  j;
//     while(args[i]) {
//         j = 0;
        
//     }
// }


// jait-chd@c1r3p11:~$ export a=adasdaa  5=dasada =
// bash: export: `5=dasada': not a valid identifier
// bash: export: `=': not a valid identifier
// jait-chd@c1r3p11:~$

int	check_valid_id(char c)
{
	if ((c <= 'a' && c >= 'z') || (c <= 'A' && c >= 'Z'))
		return (0);
	return (1);
}

// no spesial symbols as 2nd arg also no numbers
int	ft_export(char **args)
{
	int		i;
	int		j;
	t_env	*env;
	char	*eq;

	i = 1;
	j = 0;
	if (!args[i])
	{
		env = static_info()->env;
		while (env)
		{
			printf("declare -x %s\n", env->s);
			env = env->next;
		}
		return (0);
	}
	while (args[2][j])
	{
		if ((args[2][j] >= '0' && args[2][j] <= '9'))
		{
			ft_putstr_fd(args[2], 2);
			ft_putendl_fd(" : not a valid identifier", 2);
			static_info()->exit_status = 1;
		}
		j++;
	}
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			*eq = '\0';
			set_env(&static_info()->env, args[i], eq + 1);
		}
		else
			set_env(&static_info()->env, args[i], "");
		i++;
	}
	return (0);
}
