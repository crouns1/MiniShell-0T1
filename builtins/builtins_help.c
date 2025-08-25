/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:38:57 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/25 15:45:24 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_array(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**arr;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = ft_malloc(sizeof(char *) * (count + 1));
	count = 0;
	tmp = env;
	while (tmp)
	{
		arr[count++] = ft_strdup(tmp->s);
		tmp = tmp->next;
	}
	arr[count] = NULL;
	return (arr);
}
