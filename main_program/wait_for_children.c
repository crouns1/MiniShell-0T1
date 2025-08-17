/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:21:12 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/16 20:21:38 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_children(pid_t *pids, int count)
{
	int i;
	int status;
	t_info *info;

	info = static_info();
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				info->exit_status = WEXITSTATUS(status);
			else
				info->exit_status = 1;
		}
		i++;
	}
}