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
		node = ft_malloc(sizeof(t_env));
		node->s = ft_substr(env[i], ft_strlen(env[i]));
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
