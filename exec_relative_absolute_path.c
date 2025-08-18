/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_relative_absolute_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/18 22:14:41 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_absolute_path(t_list *exec, char **env)
{
    if (!exec->cmds[0])
        exit(0);
    if (exec->cmds[0][0] == '/' || (exec->cmds[0][0] == '.' ))
    {
        if(!ft_strncmp(exec->cmds[0], ".", ft_strlen(exec->cmds[0])))
        {
		ft_putstr_fd(" .: filename argument required\n", 2);
		exit(2);
	}
	if (!ft_strncmp(exec->cmds[0], "..", ft_strlen(exec->cmds[0])))
	{
		ft_putstr_fd(" ..: command not found\n", 2);
		exit(127);
    }
        if(check_dir(exec->cmds[0]))
        {
            ft_putstr_fd(exec->cmds[0] , 2);
            ft_putendl_fd(" : Is a directory" , 2);
            exit(126);
        }
        check_access_abs_path(exec);
        if (execve(exec->cmds[0], exec->cmds, env) == -1)
        {
            ft_putstr_fd("error : exceve failed" , 2);
            exit(1);
        }
    }
}

static void try_exec(t_list *exec, char **env, int i)
{
    exec->path = join_by_order(exec->paths[i], '/', exec->cmds[0]);
    if(check_dir(exec->path))
    {
        free(exec->path);
        exec->path = NULL;
        return;
    }
    if (exec->path && access(exec->path, X_OK | F_OK) == 0)
    {
        if (execve(exec->path, exec->cmds, env) == -1)
        {
            ft_putendl_fd("error : execve failed" , 2);
            free(exec->path);
            exit(1);
        }
    }
    free(exec->path);
    exec->path = NULL;
}


void execute_relative_path(t_list *exec, char **env)
{
    int i;

    if (!exec->cmds[0])
        exit(0);
    check_relat_path_edge_cases(exec);
    exec->paths = extract_paths(env, exec);
    if (!exec->paths)
    {
         ft_putstr_fd(exec->cmds[0] , 2);
        ft_putendl_fd(" : command not found" , 2);
        exit(127);
    }
    i = 0;
    while (exec->paths[i])
    {
        try_exec(exec, env, i);
        i++;
    }
}
