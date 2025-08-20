/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-getenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:57:12 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/20 02:30:54 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env(t_env *env, char *s)
{
	size_t	key_len;
	t_env	*current;

	key_len = 0;
	current = env;
	while (s[key_len] && s[key_len] != '=')
		key_len++;
	while (current)
	{
		if (ft_strncmp(current->s, s, key_len) == 0
			&& current->s[key_len] == '=')
			return (ft_substr(current->s + key_len + 1, ft_strlen(current->s)
					- (key_len + 1)));
		current = current->next;
	}
	return (ft_substr("", 1));
}

static char	*itoa(int n)
{
	int		i;
	int		tmp;
	char	*s;

	i = 0;
	if (n == 0)
		return (ft_substr("0", 1));
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		i++;
	}
	s = ft_malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	while (i--)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
char	*ft_getenv(char *token, int *len)
{
	char	*s;

	s = ft_substr((token + 1), *len - 1);
	if (s[0] == '?' && !s[1])
		s = itoa(static_info()->exit_status);
	else
		s = get_env(static_info()->env, s);
	*len = ft_strlen(s);
	return (s);
}
