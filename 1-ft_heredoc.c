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


static void	setup_signals_heredoc_child(void)
{
	signal(SIGINT, SIG_DFL);

}

static void	setup_signals_heredoc_parent(void)
{
	signal(SIGINT, SIG_IGN);
}


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

// static char	*quotes(char *s, int *f)
// {
// 	t_split	*tmp;

// 	tmp = ft_malloc(sizeof(t_split));
// 	tmp->string = s;
// 	tmp->map = fill_str(ft_strlen(s), '0');
// 	tmp->next = NULL;
// 	tmp = remove_quotes(tmp);
// 	*f = 0;
// 	if (ft_strncmp(s, tmp->string, ft_strlen(s)))
// 		*f = 1;
// 	return (tmp->string);
// }

// Returns 1 if the delimiter contains any quotes, 0 otherwise
static int	has_quotes(const char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			return (1);
		s++;
	}
	return (0);
}

// Remove quotes from delimiter for comparison, but keep info if quoted
static char	*strip_quotes(char *s)
{
	t_split	*tmp;
	char	*result;

	tmp = ft_malloc(sizeof(t_split));
	tmp->string = s;
	tmp->map = fill_str(ft_strlen(s), '0');
	tmp->next = NULL;
	tmp = remove_quotes(tmp);
	result = tmp->string;
	return (result);
}

static void	child(int fd, char *delimiter, int quoted)
{
	char	*s = NULL;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			static_info()->exit_status = 0;
			break ;
		}
		else if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (!quoted)
		{
			s = NULL;
			get_variables_heredoc(line, &s);
		}
		else
			s = line;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		if (!quoted)
			free(line);
		s = NULL;
	}
	exit(0);
}

int	heredocument(char *orig_delim)
{
	int		quoted;
	int		fd;
	char	*name;
	pid_t	pid;
	int		status;
	char	*delimiter;

	quoted = has_quotes(orig_delim);
	delimiter = strip_quotes(orig_delim);
	name = get_name();
	fd = open(name, O_CREAT | O_RDWR, 0644);
	setup_signals_heredoc_parent();
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("Error : fork failed on herdoc" , 2);
	if (pid == 0)
	{
		setup_signals_heredoc_child();
		child(fd, delimiter, quoted);
		close(fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	setup_signals_parent();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			static_info()->exit_status = 130;
		}
		return (-1);
	}
	static_info()->exit_status = 0;
	close(fd);
	fd = open(name, O_RDWR);
	unlink(name);
	return (fd);
}

int	ft_heredoc(t_list *list)
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
			{
				r->fd = heredocument(r->token);
				if(r->fd == -1)
					return 0;
			}
			r = r->next;
		}
		tmp = tmp->next;
	}
	return 1;
}
