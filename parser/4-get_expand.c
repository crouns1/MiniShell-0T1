/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-get_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:47:30 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/19 02:04:40 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	get_len(char *s, int reset)
{
	static int	in_single;
	static int	in_double;
	int			i;

	if (reset)
		return (in_single = in_double = 0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (s[i] == '"' && !in_single)
			in_double = !in_double;
		else if (!in_single && s[i] == '$' && (ft_strchr(ISVAL1, s[i + 1])
				|| s[i + 1] == '?') && s[i + 1])
			break ;
		i++;
	}
	return (i);
}

static int	get_var_len(char *s)
{
	int	len;

	len = 1;
	if (s[len] == '?')
		return (2);
	while (s[len] && (ft_strchr(ISVAL1, s[len]) || ft_strchr(ISVAL2, s[len])))
		len++;
	return (len);
}

char	*fill_str(int len, char c)
{
	char	*str;
	int		i;

	str = ft_malloc(len + 1);
	i = 0;
	while (i < len)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

void	get_variables(char *token, char **string, char **map)
{
	int	len;
	int	tmp;

	while (*token)
	{
		len = get_len(token, 0);
		*string = ft_strjoin(*string, ft_substr(token, len));
		*map = ft_strjoin(*map, fill_str(len, '0'));
		token += len;
		if (!*token)
			break ;
		len = get_var_len(token);
		tmp = len;
		*string = ft_strjoin(*string, ft_getenv(token, &len));
		*map = ft_strjoin(*map, fill_str(len, '1'));
		token += tmp;
	}
	get_len(NULL, 1);
}
