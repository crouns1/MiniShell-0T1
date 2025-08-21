/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:57:21 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 18:08:46 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	finalize_execution(int prev_fd, pid_t *pids, int cmd_count)
{
	if (prev_fd != -1)
		close(prev_fd);
	wait_children(pids, cmd_count);
	// free(pids);
}

static void	close_heredoc(t_list *list)
{
	t_rediraction	*r;

	while (list)
	{
		r = list->rediraction;
		while (r)
		{
			if (r->type == TOKEN_HEREDOC)
				close(r->fd);
			r = r->next;
		}
		list = list->next;
	}
}

static void	run_commands(t_list *cmds, char **env, pid_t *pids, int prev_fd)
{
	int	pipe_fd[2];
	int	i;

	i = 0;
	while (cmds)
	{
		if (prepare_pipe(cmds, pipe_fd) == -1)
			break ;
		pids[i] = fork();
		if (pids[i] == -1)
			break ;
		if (pids[i] == 0)
		{
			setup_signals_child();
			child_process(cmds, &env, prev_fd, pipe_fd);
		}
		close_heredoc(cmds);
		parent_process(&prev_fd, cmds, pipe_fd);
		cmds = cmds->next;
		i++;
	}
	finalize_execution(prev_fd, pids, i);
}

void	execution(t_list *cmds)
{
	pid_t	*pids;
	int		prev_fd;
	int		cmd_count;
	char	**env;

	signal(SIGINT, SIG_IGN);
	env = env_to_array(static_info()->env);
	cmd_count = init_pids(cmds, &pids, &prev_fd);
	if (cmd_count < 0)
		return ;
	run_commands(cmds, env, pids, prev_fd);
}
