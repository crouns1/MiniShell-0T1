/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:50:39 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 15:37:41 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_dir(const char *path)
{
    struct stat a;

    if (stat(path, &a) != 0) {
        return 0;
    }
    return S_ISDIR(a.st_mode);
}

void check_access_abs_path(t_list *exec) {
    if(access(exec->cmds[0] , F_OK) == -1) {
        ft_putstr_fd(exec->cmds[0] , 2);
        ft_putendl_fd(" : No such file or directory" , 2);
            exit(127);
    } 
    if(access(exec->cmds[0] , X_OK) == -1) {
        ft_putstr_fd(exec->cmds[0] , 2);
        ft_putendl_fd(" : permission denied" , 2);
        exit(126);
    }
}

void check_relat_path_edge_cases(t_list *exec ) {
     if(!ft_strncmp(exec->cmds[0], ".", ft_strlen(exec->cmds[0])))
    {
        ft_putstr_fd(exec->cmds[0] , 2);
        ft_putendl_fd(" : command not found" , 2);
        exit(127);
    }
    else if(!ft_strncmp(exec->cmds[0], "..", ft_strlen(exec->cmds[0])))
    {
         ft_putstr_fd(exec->cmds[0] , 2);
        ft_putendl_fd(" : command not found" , 2);
        exit(127);
    }
}