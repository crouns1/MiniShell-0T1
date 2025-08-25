/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:32:35 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/21 12:57:20 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	sighandler_child(int sig)
{
	(void)sig;
	ft_free_all();
	free_env(static_info()->env);
	printf("\n");
	exit(130);
}

void	setup_signals_heredoc_child(void)
{
	signal(SIGINT, sighandler_child);
}

void	setup_signals_heredoc_parent(void)
{
	signal(SIGINT, SIG_IGN);
}

char	*get_name(void)
{
	static char		buf[12];
	unsigned char	c;
	int				fd;
	int				i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (".12PIIBpiin");
	i = 1;
	while (i < 11)
	{
		if (read(fd, &c, 1) != 1)
		{
			close(fd);
			return (".12PIIBpiin");
		}
		if (c >= 33 && c <= 126)
			buf[i++] = c;
	}
	buf[0] = '.';
	buf[11] = '\0';
	close(fd);
	return (buf);
}

char	*quotes(char *s, int *quoted)
{
	t_split	*tmp;

	tmp = ft_malloc(sizeof(t_split));
	tmp->string = s;
	tmp->map = fill_str(ft_strlen(s), '0');
	tmp->next = NULL;
	tmp = remove_quotes(tmp);
	*quoted = 0;
	if (ft_strncmp(s, tmp->string, ft_strlen(s)))
		*quoted = 1;
	return (tmp->string);
}
