/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 16:44:55 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_sig;

static bool	is_continue(char	*line)
{
	if (!line)
		return (false);
	if (ft_strncmp(line, "\0", 1) == 0)
		return (true);
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		ft_putendl_fd("line too long", STDERR_FILENO);
		return (true);
	}
	return (false);
}

static int	init(void)
{
	set_exit_status(0);
	init_environ();
	return (0);
}

static char	*input(void)
{
	char	*line;

	g_sig = 0;
	rl_event_hook = rl_status_checker;
	activate_signal();
	line = readline("minishell> ");
	deactivate_signal();
	return (line);
}

static bool	is_continue_input(char *line)
{
	if (g_sig != 0)
	{
		set_exit_status(130);
		free (line);
		return (true);
	}
	if (is_continue(line))
	{
		free (line);
		return (true);
	}	
	return (false);
}

int	main(void)
{
	char	*line;
	int		ret;

	ret = init();
	while (1)
	{
		line = input();
		if (!line)
			break ;
		if (is_continue_input(line))
			continue ;
		add_history(line);
		ret = executor(parser(lexer(line)));
	}
	printf("exit\n");
	return (ret);
}
