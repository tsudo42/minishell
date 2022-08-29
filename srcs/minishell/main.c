/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:23:26 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_internal.h"

volatile sig_atomic_t	g_sig;

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
	return (0);
}

static char	*input(void)
{
	char	*line;

	g_sig = 0;
	if (ready_signal() != 0)
	{
		perror(MAIN_ERRMSG ": signal");
		return (NULL);
	}
	line = readline("minishell> ");
	if (cleanup_signal() != 0)
	{
		free (line);
		perror(MAIN_ERRMSG ": signal");
		return (NULL);
	}
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
	free_environ();
	printf("exit\n");
	return (ret);
}
