/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wht_to_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:40:19 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/25 11:55:03 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup_std_fds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
	if (*in == -1 || *out == -1)
	{
		if (*in != -1)
			close(*in);
		if (*out != -1)
			close(*out);
		return (1);
	}
	return (0);
}

void	restore_std_fds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

int	check_what_to_execute(t_list *list)
{
	t_info	*info;
	int		saved_in;
	int		saved_out;

	if (list->next || !is_builtin(list->cmds[0]))
		return (0);
	if (dup_std_fds(&saved_in, &saved_out) != 0)
	{
		static_info()->exit_status = 1;
		return (1);
	}
	if (handle_redirections(list) == -1)
	{
		restore_std_fds(saved_in, saved_out);
		return (1);
	}
	info = static_info();
	info->exit_status = run_builtin(list->cmds);
	restore_std_fds(saved_in, saved_out);
	return (1);
}
