/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-split_and_unquote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:46:38 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/17 12:35:29 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_split	*new_node(void)
{
	t_split	*node;

	node = ft_malloc(sizeof(t_split));
	node->string = NULL;
	node->map = NULL;
	node->next = NULL;
	return (node);
}

static t_split	*null_case(char *s)
{
	t_split	*node;

	(void)s;
	node = new_node();
	node->string = ft_substr("", 1);
	return (node);
}

static int	getlen(char *s, char *map)
{
	int	c;
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && map[i] != '1')
		{
			c = s[i];
			i++;
			while (s[i])
			{
				if (s[i] == c && map[i] == '0')
					break ;
				i++;
			}
			i++;
			continue ;
		}
		if (ft_strchr(WHITESPACES, s[i]))
			break ;
		i++;
	}
	return (i);
}

static void	create_node(t_split **list, t_split **tmp)
{
	if (!*list)
	{
		*list = new_node();
		*tmp = *list;
	}
	else
	{
		(*tmp)->next = new_node();
		*tmp = (*tmp)->next;
	}
}

t_split	*split_and_unquotes(char *string, char *map)
{
	int		i;
	int		len;
	int		start;
	t_split	*list;
	t_split	*tmp;

	i = 0;
	list = NULL;
	tmp = NULL;
	while (string[i])
	{
		while (string[i] && ft_strchr(WHITESPACES, string[i]))
			i++;
		if (!string[i])
			break ;
		start = i;
		create_node(&list, &tmp);
		len = getlen(string + start, map + start);
		tmp->string = ft_substr(string + start, len);
		tmp->map = ft_substr(map + start, len);
		i += len;
	}
	if (!*string || !list)
		return (null_case(string));
	return (remove_quotes(list));
}
