/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:45:48 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 15:36:52 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") || !strcmp(cmd, "pwd")
		|| !strcmp(cmd, "env") || !strcmp(cmd, "exit") || !strcmp(cmd, "export")
		|| !strcmp(cmd, "unset"));
}

int	run_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (1);
	if (!strcmp(cmd[0], "echo"))
		return (ft_echo(cmd));
	if (!strcmp(cmd[0], "cd"))
		return (ft_cd(cmd));
	if (!strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	if (!strcmp(cmd[0], "env"))
		return (ft_env());
	if (!strcmp(cmd[0], "export"))
		return (ft_export(cmd));
	if (!strcmp(cmd[0], "unset"))
		return (ft_unset(cmd));
	if (!strcmp(cmd[0], "exit"))
		return (ft_exit(cmd));
	return (1);
}
