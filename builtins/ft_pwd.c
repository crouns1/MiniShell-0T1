/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:23 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 15:37:19 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	char	*buf;

	pwd = get_env_value(static_info()->env, "PWD");
	if (!pwd)
	{
		buf = getcwd(NULL, 0);
		if (buf)
		{
			ft_putendl_fd(buf, 1);
			free(buf);
		}
		else
			ft_putendl_fd("error : pwd failed", 2);
	}
	else
		ft_putendl_fd(pwd , 1);

	return (0);
}
