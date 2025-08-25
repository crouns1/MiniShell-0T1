/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-ft_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:58:52 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/18 09:02:00 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static t_tokens	*create_token_node(char *str, int flag)
{
	t_tokens	*new_node;

	new_node = ft_malloc(sizeof(t_tokens));
	new_node->string = str;
	new_node->flag = flag;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_tokens	*split_to_tokens(t_split *split_list, int flag)
{
	t_tokens	*head;
	t_tokens	*current;
	t_tokens	*new_node;

	head = NULL;
	current = NULL;
	while (split_list)
	{
		new_node = create_token_node(split_list->string, flag);
		if (!head)
			head = new_node;
		else
		{
			current->next = new_node;
			new_node->prev = current;
		}
		current = new_node;
		split_list = split_list->next;
	}
	return (head);
}

static void	append_to_list(t_tokens **tokens, t_split *new_lst, int flag)
{
	t_tokens	*new_tokens;
	t_tokens	*current;
	t_tokens	*next;

	new_tokens = split_to_tokens(new_lst, flag);
	current = *tokens;
	current->string = new_tokens->string;
	next = current->next;
	current->next = new_tokens->next;
	while (current->next)
		current = current->next;
	current->next = next;
	if (next)
		next->prev = current;
	*tokens = current;
}

static t_tokens	*remove_node(t_tokens **head, t_tokens *node)
{
	t_tokens	*next_node;

	if (!head || !*head || !node)
		return (NULL);
	next_node = node->next;
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	node->prev = NULL;
	node->next = NULL;
	return (next_node);
}

t_tokens	*ft_expand(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		*string;
	char		*map;

	tmp = tokens;
	while (tmp)
	{
		string = NULL;
		map = NULL;
		if (tmp->flag == TOKEN_WORD || tmp->flag == TOKEN_FILENAME)
		{
			get_variables(tmp->string, &string, &map);
			if (check_string(string))
			{
				tmp = remove_node(&tokens, tmp);
				continue ;
			}
			tmp->string = string;
			append_to_list(&tmp, split_and_unquotes(string, map), tmp->flag);
		}
		tmp = tmp->next;
	}
	return (tokens);
}
