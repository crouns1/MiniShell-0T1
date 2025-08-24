/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/24 21:01:46 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	history(char *line)
{
	if (!line || !*line)
		return ;
	add_history(line);
}

void	initialise_info(char **env)
{
	t_info	*info;

	info = static_info();
	info->env = arr_list(env);
	info->exit_status = 0;
}

static void	shell_loop(void)
{
	char	*line;
	t_list	*list;

	while (1)
	{
		setup_signals_parent();
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit" , 1);
			clean_exit(0);
		}
		history(line);
		if (check_input(line))
			continue ;
		list = input_analysis(line);
		if (!list)
			continue ;
		if(!ft_heredoc(list))
			continue ;
		if (!check_what_to_execute(list))
			execution(list);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	initialise_info(env);
	shell_loop();
	ft_free_all();
	return (0);
}
