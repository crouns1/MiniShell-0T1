	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   ft_env.c                                           :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2025/07/13 21:46:16 by jait-chd          #+#    #+#             */
	/*   Updated: 2025/08/21 15:37:02 by jait-chd         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "../minishell.h"

	int	ft_env(void)
	{
		t_env	*env;

		env = static_info()->env;
		while (env)
		{
			if (ft_strchr(env->s, '='))
				printf("%s\n", env->s);
			env = env->next;
		}
		return (0);
	}
