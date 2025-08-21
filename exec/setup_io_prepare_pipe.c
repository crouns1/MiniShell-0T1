/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_io_prepare_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:25:59 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 15:38:11 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_io(int prev_fd, int pipe_fd[2], int has_next)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (has_next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
}

int	prepare_pipe(t_list *cmds, int pipe_fd[2])
{
	t_info	*info;

	if (!cmds->next)
		return (0);
	info = static_info();
	if (pipe(pipe_fd) == -1)
	{
		ft_putendl_fd("error : pipe failed", 2);
		info->exit_status = 1;
		return (-1);
	}
	return (0);
}
