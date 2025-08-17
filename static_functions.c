/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:17:30 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/17 04:57:08 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
