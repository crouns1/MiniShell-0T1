/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-ft_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:59:57 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/18 09:02:13 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	check_string(char *s)
{
	while (ft_strchr(WHITESPACES, *s) && *s)
		s++;
	if (!s || !*s)
		return (1);
	return (0);
}

static void	copy_strings(char *result, char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;

	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	result = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	copy_strings(result, s1, s2);
	return (result);
}
