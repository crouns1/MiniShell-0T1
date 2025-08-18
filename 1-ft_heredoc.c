/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-ft_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:29:55 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/18 12:40:17 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_name(void)
{
	static char		buf[9];
	unsigned char	c;
	int				fd;
	int				i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return ("12345678");
	i = 0;
	while (i < 8)
	{
		if (read(fd, &c, 1) != 1)
		{
			close(fd);
			return ("12345678");
		}
		if (c >= 33 && c <= 126)
			buf[i++] = c;
	}
	buf[8] = '\0';
	close(fd);
	return (buf);
}

static char	*quotes(char *s, int *f)
{
	t_split	*tmp;

	tmp = ft_malloc(sizeof(t_split));
	tmp->string = s;
	tmp->map = fill_str(ft_strlen(s), '0');
	tmp->next = NULL;
	tmp = remove_quotes(tmp);
	*f = 0;
	if (ft_strncmp(s, tmp->string, ft_strlen(s)))
		*f = 1;
	return (tmp->string);
}

static void	child(int fd, char *delimiter, int f)
{
	char	*s;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("%s (wanted '%s')\n", delimiter, delimiter);
			break ;
		}
		else if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (!f)
			get_variables_heredoc(line, &s);
		else
			s = line;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(line);
		s = NULL;
	}
}

int	heredocument(char *delimiter)
{
	int		f;
	int		fd;
	char	*name;
	pid_t	pid;

	name = get_name();
	delimiter = quotes(delimiter, &f);
	fd = open(name, O_CREAT | O_RDWR, 0644);
	pid = fork();
	if (pid == -1)
		perror("Error");
	if (pid == 0)
	{
		child(fd, delimiter, f);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close(fd);
	fd = open(name, O_RDWR);
	unlink(name);
	return (fd);
}

void	ft_heredoc(t_list *list)
{
	t_list			*tmp;
	t_rediraction	*r;

	tmp = list;
	while (tmp)
	{
		r = tmp->rediraction;
		while (r)
		{
			if (r->type == TOKEN_HEREDOC)
				r->fd = heredocument(r->token);
			r = r->next;
		}
		tmp = tmp->next;
	}
}
