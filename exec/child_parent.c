/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:24:03 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/25 11:55:07 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_exit(int status)
{
	ft_free_all();
	exit(status);
}

void	child_process(t_list *cmds, char ***env, int prev_fd, int pipe_fd[2])
{
	setup_io(prev_fd, pipe_fd, cmds->next != NULL);
	if (handle_redirections(cmds) == -1)
		clean_exit(static_info()->exit_status);
	if (is_builtin(cmds->cmds[0]))
		clean_exit(run_builtin(cmds->cmds));
	execute_absolute_path(cmds, *env);
	execute_relative_path(cmds, *env);
	ft_putstr_fd(cmds->cmds[0], 2);
	ft_putendl_fd(" : command not found", 2);
	clean_exit(127);
}

void	parent_process(int *prev_fd, t_list *cmds, int pipe_fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmds->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}
