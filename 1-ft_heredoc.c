/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-ft_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:29:55 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/20 00:02:09 by jait-chd         ###   ########.fr       */
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
	// setup_signals_heredoc();

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
	// int status = 0;
	// int sig;
	name = get_name();
	delimiter = quotes(delimiter, &f);
	fd = open(name, O_CREAT | O_RDWR, 0644);
	// signal(SIGINT , SIG_IGN);
		// setup_signals_heredoc();

	pid = fork();
	if (pid == -1)
	ft_putendl_fd("Error : fork failed on herdoc" , 2);
	if (pid == 0)
	{
		// setup_signals_heredoc();
		// signal(SIGINT , SIG_DFL);
		child(fd, delimiter, f);
		exit(0);
	}
	waitpid(pid, NULL, 0);
		//  if (WIFEXITED(status))
		// 	 static_info()->exit_status = 0;
		// 	if (WIFSIGNALED(status))
		// 	{
		// 		sig = WTERMSIG(status);
		// 		if (sig == SIGINT)
		// 		{
		// 			write(1, "xxxxxxxxxxx\n", 13);
		// 			static_info()->exit_status = 130;
		// 		}
		// 		else if (sig == SIGQUIT)
		// 		{
		// 			write(1, "core dump\n", 11);
		// 			static_info()->exit_status = 131;
		// 			// info->exit_status = 131;
		// 		}
		// 	}
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
