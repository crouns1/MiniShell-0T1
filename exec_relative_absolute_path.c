/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_relative_absolute_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/18 05:33:38 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_dir(const char *path)
{
    struct stat a;

    if (stat(path, &a) != 0) {
        return 0;
    }
    return S_ISDIR(a.st_mode);
}

void execute_absolute_path(t_list *exec, char **env)
{
    if (!exec->cmds[0])
        exit(0);
    if (exec->cmds[0][0] == '/' || (exec->cmds[0][0] == '.' ))
    {
        if(check_dir(exec->cmds[0]))
        {
            fprintf(stderr, "%s: Is a directory\n", exec->cmds[0]);
            exit(126);
        }
        if (access(exec->cmds[0], F_OK) == -1)
        {
            fprintf(stderr, "%s: No such file or directory\n", exec->cmds[0]);
            exit(127);
        }
        else if (access(exec->cmds[0], X_OK) == -1)
        {
            fprintf(stderr, "%s: permission denied\n", exec->cmds[0]);
            exit(126);
        }
        if (execve(exec->cmds[0], exec->cmds, env) == -1)
        {
            perror("execve");
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
            perror("execve");
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
    if(!ft_strncmp(exec->cmds[0], ".", ft_strlen(exec->cmds[0])))
    {
        fprintf(stderr, "%s: command not found\n", exec->cmds[0]);
        exit(127);
    }
    else if(!ft_strncmp(exec->cmds[0], "..", ft_strlen(exec->cmds[0])))
    {
        fprintf(stderr, "%s: command not found\n", exec->cmds[0]);
        exit(127);
    }
    exec->paths = extract_paths(env, exec);
    if (!exec->paths)
    {
        fprintf(stderr, "%s: command not found\n", exec->cmds[0]);
        exit(127);
    }
    i = 0;
    while (exec->paths[i])
    {
        try_exec(exec, env, i);
        i++;
    }
}


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec_relative_absolute_path.c                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
// /*   Updated: 2025/08/18 23:00:00 by jait-chd         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"
// #include <sys/stat.h>
// #include <unistd.h>
// #include <stdlib.h>

// static int	check_dir(const char *path)
// {
// 	struct stat st;

// 	if (stat(path, &st) != 0)
// 		return (0);
// 	return (st.st_mode & S_IFMT) == S_IFDIR;
// }

// void	execute_absolute_path(t_list *exec, char **env)
// {
// 	if (!exec->cmds[0])
// 		exit(0);

// 	/* special cases: . and .. */
// 	if (!ft_strncmp(exec->cmds[0], ".", ft_strlen(exec->cmds[0])))
// 	{
// 		ft_putstr_fd("minishell: .: filename argument required\n", 2);
// 		exit(2);
// 	}
// 	if (!ft_strncmp(exec->cmds[0], "..", ft_strlen(exec->cmds[0])))
// 	{
// 		ft_putstr_fd("minishell: ..: command not found\n", 2);
// 		exit(127);
// 	}

// 	if (check_dir(exec->cmds[0]))
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(exec->cmds[0], 2);
// 		ft_putstr_fd(": is a directory\n", 2);
// 		exit(126);
// 	}
// 	if (access(exec->cmds[0], F_OK) == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(exec->cmds[0], 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		exit(127);
// 	}
// 	if (access(exec->cmds[0], X_OK) == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(exec->cmds[0], 2);
// 		ft_putstr_fd(": Permission denied\n", 2);
// 		exit(126);
// 	}
// 	execve(exec->cmds[0], exec->cmds, env);
// 	perror("execve");
// 	exit(1);
// }

// static void	try_exec(t_list *exec, char **env, int i)
// {
// 	exec->path = join_by_order(exec->paths[i], '/', exec->cmds[0]);
// 	if (exec->path && !check_dir(exec->path) &&
// 		access(exec->path, X_OK | F_OK) == 0)
// 	{
// 		execve(exec->path, exec->cmds, env);
// 		perror("execve");
// 		free(exec->path);
// 		exit(1);
// 	}
// 	free(exec->path);
// 	exec->path = NULL;
// }

// void	execute_relative_path(t_list *exec, char **env)
// {
// 	int	i;

// 	if (!exec->cmds[0])
// 		exit(0);

// 	/* handle "." and ".." like bash */
// 	if (!ft_strncmp(exec->cmds[0], ".", ft_strlen(exec->cmds[0])))
// 	{
// 		ft_putstr_fd("minishell: .: filename argument required\n", 2);
// 		exit(2);
// 	}
// 	if (!ft_strncmp(exec->cmds[0], "..", ft_strlen(exec->cmds[0])))
// 	{
// 		ft_putstr_fd("minishell: ..: command not found\n", 2);
// 		exit(127);
// 	}

// 	exec->paths = extract_paths(env, exec);
// 	if (!exec->paths)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(exec->cmds[0], 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		exit(127);
// 	}
// 	i = 0;
// 	while (exec->paths[i])
// 	{
// 		try_exec(exec, env, i);
// 		i++;
// 	}
// 	// ft_putstr_fd("minishell: ", 2);
// 	// ft_putstr_fd(exec->cmds[0], 2);
// 	// ft_putstr_fd(": command not found\n", 2);
// 	// exit(127);
// }
