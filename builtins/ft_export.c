/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:13:33 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/24 20:43:11 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void print_env_list(t_env *env)
{
	while (env)
	{
		printf("declare -x %s\n", env->s);
		env = env->next;
	}
}

static int handle_export_arg(char *arg)
{
	char *eq;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*eq = '\0';
		set_env(&static_info()->env, arg, eq + 1);
	}
	else
	{
		set_env(&static_info()->env, arg, NULL);
	}
	return (0);
}

int	ft_export(char **args)
{
	int		i;
	int		ret;

	ret = 0;
	if (!args[1])
	{
		print_env_list(static_info()->env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(args[i]))
			ret = 1;
		i++;
	}
	static_info()->exit_status = ret;
	return (ret);
}
