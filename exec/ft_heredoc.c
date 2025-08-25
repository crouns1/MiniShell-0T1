/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:29:55 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/25 11:54:48 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include <unistd.h>

static void	child(int fd, char *delimiter, int quoted)
{
	char	*s;
	char	*line;

	while (1)
	{
		s = NULL;
		line = readline("> ");
		if (!line)
		{
			printf("%s (wanted '%s')\n", HEREDOCERR, delimiter);
			break ;
		}
		else if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (!quoted)
			get_variables_heredoc(line, &s);
		else
			s = line;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

static void	ft_child(t_fd fd, char *delimiter, int quoted)
{
	setup_signals_heredoc_child();
	child(fd.fd_write, delimiter, quoted);
	close(fd.fd_read);
	close(fd.fd_write);
	ft_free_all();
	exit(0);
}

int	heredocument(char *delimiter)
{
	t_fd	fd;
	int		quoted;
	int		status;
	char	*name;
	pid_t	pid;

	name = get_name();
	delimiter = quotes(delimiter, &quoted);
	fd.fd_write = open(name, O_CREAT | O_RDWR, 0644);
	fd.fd_read = open(name, O_RDWR);
	unlink(name);
	if (fd.fd_read == -1 || fd.fd_write == -1)
		return (-1);
	setup_signals_heredoc_parent();
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("Error : fork failed on herdoc", 2);
	if (pid == 0)
		ft_child(fd, delimiter, quoted);
	waitpid(pid, &status, 0);
	static_info()->exit_status = WEXITSTATUS(status);
	close(fd.fd_write);
	return (fd.fd_read);
}

int	ft_heredoc(t_list *list)
{
	t_list			*tmp;
	t_rediraction	*r;

	if (!list)
		return (1);
	tmp = list;
	while (tmp)
	{
		r = tmp->rediraction;
		while (r)
		{
			if (r->type == TOKEN_HEREDOC)
			{
				r->fd = heredocument(r->token);
				if (r->fd == -1)
				{
					ft_putendl_fd("unable to open a file!", 2);
					return (1);
				}
			}
			r = r->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
