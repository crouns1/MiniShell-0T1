/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:46:55 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/16 20:47:05 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int init_pids(t_list *cmds, pid_t **pids, int *prev_fd)
{
    int count;

    count = list_size(cmds);
    *pids = malloc(sizeof(pid_t) * count);
    if (!*pids)
        return (-1);
    *prev_fd = -1;
    return (count);
}