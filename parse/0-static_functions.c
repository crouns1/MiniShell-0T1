/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-static_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:17:30 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/21 15:35:23 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gc	**static_gc(void)
{
	static t_gc	*list;

	return (&list);
}

t_info	*static_info(void)
{
	static t_info	info;

	return (&info);
}
