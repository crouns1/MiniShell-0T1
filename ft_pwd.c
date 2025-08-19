/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:23 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/19 00:13:21 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ft_pwd(char **args)
{
		char cwd[1024];
	char	cwd[1024];

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
/* If you have your own env getter,
	replace getenv("PWD") with ms_getenv("PWD") */
int	ft_pwd(char **args)
{
	char cwd[1024];
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (write(2, "minishell: pwd: invalid option\n", 31), 1);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		/* Only special-case “directory vanished / inaccessible” */
		if (errno == ENOENT || errno == EACCES)
		{
			const char *lpwd = getenv("PWD"); /* or ms_getenv("PWD") */
			if (lpwd && *lpwd)
			{
				write(1, lpwd, strlen(lpwd));
				write(1, "\n", 1);
				return (0);
			}
		}
		/* Otherwise keep your original behavior */
		perror("pwd");
		return (1);
	}
	write(1, cwd, strlen(cwd));
	write(1, "\n", 1);
	return (0);
}


// typedef struct s_env
// {
//     char            *key;
//     char            *value;
//     int             exported;
//     struct s_env    *next;
// }   t_env;

// /* ------------ utils ------------ */
// static char *ft_strdup_(const char *s)
// {
//     size_t len = strlen(s);
//     char *dup = malloc(len + 1);
//     if (!dup)
//         return (NULL);
//     memcpy(dup, s, len);
//     dup[len] = '\0';
//     return (dup);
// }

// static t_env *find_env(t_env *env, const char *key)
// {
//     while (env)
//     {
//         if (strcmp(env->key, key) == 0)
//             return (env);
//         env = env->next;
//     }
//     return (NULL);
// }

// static void set_env(t_env **env, const char *key, const char *value)
// {
//     t_env *node = find_env(*env, key);

//     if (node)
//     {
//         if (node->value)
//             free(node->value);
//         node->value = ft_strdup_(value);
//         node->exported = 1;
//     }
//     else
//     {
//         node = malloc(sizeof(t_env));
//         if (!node)
//             return ;
//         node->key = ft_strdup_(key);
//         node->value = ft_strdup_(value);
//         node->exported = 1;
//         node->next = *env;
//         *env = node;
//     }
// }

// /* ------------ builtin pwd ------------ */
// int ft_pwd(t_env **env)
// {
//     char buf[4096];
//     char *cwd;
//     t_env *pwd_var;

//     cwd = getcwd(buf, sizeof(buf));
//     if (!cwd)
//     {
//         /* fallback: use PWD from env if getcwd fails */
//         pwd_var = find_env(*env, "PWD");
//         if (pwd_var && pwd_var->value)
//         {
//             write(1, pwd_var->value, strlen(pwd_var->value));
//             write(1, "\n", 1);
//             return (0);
//         }
//         return (1);
//     }
//     /* update OLDPWD before overwriting PWD */
//     pwd_var = find_env(*env, "PWD");
//     if (pwd_var && pwd_var->value)
//         set_env(env, "OLDPWD", pwd_var->value);
//     set_env(env, "PWD", cwd);

//     write(1, cwd, strlen(cwd));
//     write(1, "\n", 1);
//     return (0);
// }