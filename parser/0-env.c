/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:42:02 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/18 09:00:30 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		if (env->s)
			free(env->s);
		free(env);
		env = next;
	}
}

static char	*env_substr(char *s, int len)
{
	char	*sub;
	int		i;

	i = 0;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[i] && i < len)
	{
		sub[i] = s[i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static void	cleanup(t_env *list)
{
	free_env(list);
	ft_free_all();
	exit(EXIT_FAILURE);
}

t_env	*env_list(char **env)
{
	t_env	*list;
	t_env	*tmp;
	t_env	*node;
	int		i;

	list = NULL;
	tmp = NULL;
	i = 0;
	while (env[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			cleanup(list);
		node->s = env_substr(env[i], ft_strlen(env[i]));
		if (!node->s)
			cleanup(list);
		node->next = NULL;
		if (!list)
			list = node;
		else
			tmp->next = node;
		tmp = node;
		i++;
	}
	return (list);
}
