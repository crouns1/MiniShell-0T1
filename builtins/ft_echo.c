/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:13 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 15:36:59 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (args[i] && is_n(args[i]))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
