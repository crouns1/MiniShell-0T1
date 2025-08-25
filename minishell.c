/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:29:56 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/25 15:18:21 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	history(char *line)
{
	if (!*line)
		return ;
	add_history(line);
}

static void	initialise_info(char **env)
{
	t_info	*info;

	info = static_info();
	info->env = env_list(env);
	info->exit_status = 0;
}

static void	execute(t_list *list)
{
	if (ft_heredoc(list))
		return ;
	if (!check_what_to_execute(list))
		execution(list);
	close_heredoc(list);
}

static void	minishell(void)
{
	char	*line;
	t_list	*list;

	while (1)
	{
		setup_signals_parent();
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		history(line);
		if (check_input(line))
			continue ;
		list = input_analysis(line);
		execute(list);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	initialise_info(env);
	minishell();
	ft_free_all();
	return (static_info()->exit_status);
}
