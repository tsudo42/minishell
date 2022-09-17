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

#include "minishell.h"
#include "exec.h"
#include "environ.h"
#include "lexer.h"
#include "parser.h"
#include <errno.h>
#include <stdlib.h>

char	*input(t_environ *env);

volatile sig_atomic_t	g_sig;

static t_environ	*init(void)
{
	t_environ	*env;

	env = environ_init();
	return (env);
}

int	main(void)
{
	t_environ	*env;
	char		*line;
	int			exit_status;

	env = init();
	while (1)
	{
		line = input(env);
		if (!line)
			break ;
		executor(parser(lexer(line)), env);
	}
	exit_status = env->exit_status;
	environ_destroy(env);
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (exit_status);
}
