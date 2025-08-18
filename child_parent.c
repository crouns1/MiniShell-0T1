/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:24:03 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/18 22:27:11 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_list *cmds, char ***env, int prev_fd, int pipe_fd[2])
{
	
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	setup_io(prev_fd, pipe_fd, cmds->next != NULL);
	if (handle_redirections(cmds) == -1)
		exit(1);
	if (is_builtin(cmds->cmds[0]))
		exit(run_builtin(cmds->cmds, env));
	execute_absolute_path(cmds, *env);
	execute_relative_path(cmds, *env);
	ft_putstr_fd(cmds->cmds[0], 2);
	ft_putendl_fd(" : command not found", 2);
	exit(127);
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