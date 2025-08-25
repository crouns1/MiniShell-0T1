	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   ft_exit.c                                          :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2025/06/11 05:46:20 by jait-chd          #+#    #+#             */
	/*   Updated: 2025/08/21 15:37:11 by jait-chd         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "../minishell.h"

static int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		else
			sign = 1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - 48);
		nptr++;
	}
	return (result * sign);
}

	static int numeric(char *s)
{
    int i;

    if (!s || !*s)
        return 0;

    i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;

    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return 0;
        i++;
    }

    return 1;
}


	int	ft_exit(char **args)
	{
		int	code;
		if(isatty(0) && isatty(1))
			ft_putendl_fd("exit", 2);
		if (!args[1])
				exit(static_info()->exit_status);
		else if (!numeric(args[1]))
		{
			write(2, "minishell : exit: ", 17);
			write(2, args[1], strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			exit(2);
		}
		if (args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		code = ft_atoi(args[1]);
		exit(code);
	}
