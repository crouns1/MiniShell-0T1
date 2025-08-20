/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:42:02 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/20 04:44:27 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*arr_list(char **env)
{
	t_env	*head;
	t_env	*last;
	t_env	*node;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (env[i])
	{
		node = ft_malloc(sizeof(t_env));
		node->s = ft_substr(env[i], ft_strlen(env[i]));
		node->next = NULL;
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		i++;
	}
	return (head);
}
