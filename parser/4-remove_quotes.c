/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-remove_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:09:18 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/18 09:03:06 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	process_quotes(t_split *tmp, char *s, int *i, int *j)
{
	int	c;

	c = tmp->string[*i];
	(*i)++;
	while (tmp->string[*i])
	{
		if (tmp->string[*i] == c && tmp->map[*i] != '1')
			break ;
		s[(*j)++] = tmp->string[(*i)++];
	}
	if (tmp->string[*i] == c)
		(*i)++;
}

static void	process_string(t_split *tmp)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = ft_malloc(sizeof(char) * (ft_strlen(tmp->string) + 1));
	while (tmp->string[i])
	{
		if ((tmp->string[i] == '\'' || tmp->string[i] == '\"')
			&& tmp->map[i] == '0')
		{
			process_quotes(tmp, s, &i, &j);
			continue ;
		}
		s[j++] = tmp->string[i++];
	}
	s[j] = '\0';
	tmp->string = s;
	s = NULL;
}

t_split	*remove_quotes(t_split *list)
{
	t_split	*tmp;

	tmp = list;
	while (tmp)
	{
		process_string(tmp);
		tmp = tmp->next;
	}
	return (list);
}
