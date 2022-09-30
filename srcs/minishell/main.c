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
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

volatile sig_atomic_t	g_sig;

char	*input(t_environ *env);

int	main(int argc, char **argv)
{
	t_environ	*env;
	char		*line;
	int			exit_status;
	static int	i = 2;
	int	input_type = 0;

	env = environ_init();
	if (argc >= 2 && ft_strcmp(argv[1], "-c") == 0)
		input_type = 1;
	while (1)
	{
		if (input_type)
		{
			if (i >= argc)
				line = NULL;
			else
				line = ft_strdup(argv[i]);
			i++;
		}
		else
			line = input(env);
		if (!line)
			break ;
		env->exit_status = executor(parser(lexer(line)), env);
	}
	exit_status = env->exit_status;
	environ_destroy(env);
	if (!input_type)
		ft_dprintf(STDERR_FILENO, "exit\n");
	return (exit_status);
}
