/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:08 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/20 06:24:21 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*dir;
	char	cwd[4096];
	t_info	*info;

	info = static_info();
	if (args[1] && args[2])
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (!args[1])
		dir = get_env_value(info->env, "HOME");
	else
		dir = args[1];
	if (!dir || chdir(dir) != 0)
	{
		ft_putendl_fd("error : HOME not set", 2);
		info->exit_status = 1;
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env(&info->env, "OLDPWD", get_env_value(info->env, "PWD"));
		set_env(&info->env, "PWD", cwd);
	}
	return (0);
}

// int	ft_cd(char **args)
// {
// 	char	*path;

// 	if (args[1] && args[2])
// 		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
// 	path = args[1] ? args[1] : getenv("HOME");
// 	if (!path)
// 		return (write(2, "minishell: cd: HOME not set\n", 28), 1);
// 	if (chdir(path))
// 	{
// 		write(2, "minishell: cd: ", 15);
// 		perror(path);
// 		return (1);
// 	}
// 	return (0);
// }
