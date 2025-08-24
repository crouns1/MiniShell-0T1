/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_relative_absolute_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/24 21:38:08 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_absolute_path(t_list *exec, char **env)
{
	if (!exec->cmds[0])
		clean_exit(0);
	if (ft_strchr(exec->cmds[0], '/') || exec->cmds[0][0] == '.')
	{
		edge_check(exec);
		check_access_abs_path(exec);
		if (check_dir(exec->cmds[0]))
		{
			ft_putstr_fd(exec->cmds[0], 2);
			ft_putendl_fd(" : Is a directory", 2);
			clean_exit(126);
		}
		if (execve(exec->cmds[0], exec->cmds, env) == -1)
		{
			ft_putendl_fd("error : exec format error", 2);
			clean_exit(126);
		}
	}
}

static void	try_exec(t_list *exec, char **env, int i)
{
	exec->path = join_by_order(exec->paths[i], '/', exec->cmds[0]);
	if (check_dir(exec->path))
	{
		exec->path = NULL;
		return ;
	}
	if (exec->path && access(exec->path, F_OK) == 0)
	{
		if (access(exec->path, X_OK) == -1)
		{
			ft_putstr_fd(exec->cmds[0], 2);
			ft_putendl_fd(" : permission denied", 2);
			clean_exit(126);
		}
		if (execve(exec->path, exec->cmds, env) == -1)
		{
			ft_putendl_fd("error : exec format error", 2);
			clean_exit(126);
		}
	}
	exec->path = NULL;
}

void	execute_relative_path(t_list *exec, char **env)
{
	int	i;

	if (!exec->cmds[0])
		clean_exit(0);
	exec->paths = extract_paths(env, exec);
	if (!exec->paths)
	{
		ft_putstr_fd(exec->cmds[0], 2);
		ft_putendl_fd(" : command not found", 2);
		clean_exit(127);
	}
	i = 0;
	while (exec->paths[i])
	{
		try_exec(exec, env, i);
		i++;
	}
}
