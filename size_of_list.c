/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_of_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:28:44 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/20 00:16:31 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_size(t_list *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
