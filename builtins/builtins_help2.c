/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_help2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:44:37 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/25 15:43:51 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_env(t_env *env, char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if ((!ft_strncmp(env->s, key, len) && env->s[len] == '=')
			|| env->s[len] == '\0')
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->s, key, key_len) == 0 && env->s[key_len] == '=')
		{
			return (env->s + key_len + 1);
		}
		env = env->next;
	}
	return (NULL);
}
