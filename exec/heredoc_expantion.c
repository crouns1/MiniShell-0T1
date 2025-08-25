/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expantion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:30:02 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/25 11:54:51 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	get_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && (ft_strchr(ISVAL1, s[i + 1]) || s[i + 1] == '?')
			&& s[i + 1])
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

void	get_variables_heredoc(char *token, char **string)
{
	int	len;
	int	tmp;

	while (*token)
	{
		len = get_len(token);
		*string = ft_strjoin(*string, ft_substr(token, len));
		token += len;
		if (!*token)
			break ;
		len = get_var_len(token);
		tmp = len;
		*string = ft_strjoin(*string, ft_getenv(token, &len));
		token += tmp;
	}
}
