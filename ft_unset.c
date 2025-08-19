/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:13:26 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/19 00:13:28 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <ctype.h>
#include <string.h>

extern char	**environ;

static int	valid(char *s)
{
	int	i;

	if (!s || (!isalpha((unsigned char)s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **a, char ***e)
{
	int	i = 1, st;

	i = 1, st = 0;
	while (a[i])
	{
		if (!valid(a[i]))
			(write(2, "minishell: unset: `", 19), write(2, a[i], strlen(a[i])),
				write(2, "': not a valid identifier\n", 26), st = 1);
		else
			unsetenv(a[i]);
		i++;
	}
	*e = environ;
	static_info()->env = arr_list(*e);
	return (st);
}



// typedef struct s_env
// {
//     char            *key;
//     char            *value;
//     int             exported;
//     struct s_env    *next;
// }   t_env;

// /* ---------------- utils ---------------- */
// static int valid_identifier_unset(char *s)
// {
//     int i;

//     if (!s || (!isalpha((unsigned char)s[0]) && s[0] != '_'))
//         return (0);
//     i = 1;
//     while (s[i])
//     {
//         if (!isalnum((unsigned char)s[i]) && s[i] != '_')
//             return (0);
//         i++;
//     }
//     return (1);
// }

// /* remove node from env list */
// static void remove_env(t_env **env, const char *key)
// {
//     t_env *cur;
//     t_env *prev;

//     prev = NULL;
//     cur = *env;
//     while (cur)
//     {
//         if (strcmp(cur->key, key) == 0)
//         {
//             if (prev)
//                 prev->next = cur->next;
//             else
//                 *env = cur->next;
//             if (cur->key)
//                 free(cur->key);
//             if (cur->value)
//                 free(cur->value);
//             free(cur);
//             return ;
//         }
//         prev = cur;
//         cur = cur->next;
//     }
// }

// /* ---------------- builtin unset ---------------- */
// int ft_unset(char **args, t_env **env)
// {
//     int i;
//     int status;

//     i = 1;
//     status = 0;
//     while (args[i])
//     {
//         if (!valid_identifier_unset(args[i]))
//         {
//             write(2, "minishell: unset: `", 19);
//             write(2, args[i], strlen(args[i]));
//             write(2, "': not a valid identifier\n", 26);
//             status = 1;
//         }
//         else
//             remove_env(env, args[i]);
//         i++;
//     }
//     return (status);
// }
