/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:13:41 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/25 15:46:53 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_counting(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	ft_start_end(const char *s, size_t *i, size_t *j, char c)
{
	*j = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	while (s[*i + *j] && s[*i + *j] != c)
		(*j)++;
}

static char	*substr_from(const char *s, size_t start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = ft_malloc(len + 1);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	l;
	size_t	j;
	size_t	count;
	char	**r;

	i = 0;
	l = 0;
	if (!s)
		return (0);
	count = ft_counting(s, c);
	r = (char **)ft_malloc((count + 1) * sizeof(char *));
	while (l < count)
	{
		ft_start_end(s, &i, &j, c);
		r[l] = substr_from(s, i, j);
		i += j;
		l++;
	}
	r[count] = 0;
	return (r);
}
