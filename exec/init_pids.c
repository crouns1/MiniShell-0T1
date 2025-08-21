/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:46:55 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 16:41:49 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	init_pids(t_list *cmds, pid_t **pids, int *prev_fd)
{
	int count;

	count = list_size(cmds);
	*pids = ft_malloc(count * sizeof(pid_t));
	*prev_fd = -1;
	return (count);
}