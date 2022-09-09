/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:46:17 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_internal.h"

static bool	is_continue(char	*line)
{
	if (!line)
		return (false);
	if (ft_strncmp(line, "\0", 1) == 0)
		return (true);
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		ft_putendl_fd(MAIN_ERRMSG ": line too long", STDERR_FILENO);
		return (true);
	}
	return (false);
}

static bool	is_continue_input(char *line, t_environ *env)
{
	if (g_sig != 0)
	{
		env->exit_status = 130;
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

volatile sig_atomic_t	g_sig;

static t_environ	*init(void)
{
	t_environ	*env;

	env = environ_init();
	return (env);
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

int	main(void)
{
	t_environ	*env;
	char		*line;
	int			exit_status;

	env = init();
	while (1)
	{
		line = input();
		if (!line)
			break ;
		if (is_continue_input(line, env))
			continue ;
		add_history(line);
		executor(parser(lexer(line)), env);
	}
	exit_status = env->exit_status;
	environ_destroy(env);
	printf("exit\n");
	return (exit_status);
}
