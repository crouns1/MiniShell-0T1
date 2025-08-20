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

int	is_valid_identifier(const char *s)
{
	int i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **args)
{
	int		i;
	t_env	*env;
	char	*eq;
	int		ret;

	ret = 0;
	if (!args[1])
	{
		env = static_info()->env;
		while (env)
		{
			printf("declare -x %s\n", env->s);
			env = env->next;
		}
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
		{
			eq = ft_strchr(args[i], '=');
			if (eq)
			{
				*eq = '\0';
				set_env(&static_info()->env, args[i], eq + 1);
			}
			else
				set_env(&static_info()->env, args[i], "");
		}
		i++;
	}
	static_info()->exit_status = ret;
	return (ret);
}
