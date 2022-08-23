/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

int *exit_status(void)
{
	static int s;

	return (&s);
}



#include "environ.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
=======
*/

#define MAIN_ERRMSG "minishell"

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
/*
	if (dup2(STDERR_FILENO, MINISHELL_HEREDOC_FILENO) < 0)
	{
		perror(MAIN_ERRMSG ": init: dup2");
		exit(2);
*/
	init_environ();
//	if (init_environ() < 0)
//		exit(2);
	return (0);
}

/*
static char	*input(void)
{
	write(STDERR_FILENO, "> ", 2);
	return (get_next_line(0));
}
*/

int	main(void)
{
	char *line;
	int		ret;

	ret = init();
	while (1)
	{
		activate_signal();
		g_sig = 0;
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (g_sig != 0 || is_continue(line))
		{
			free (line);
			continue ;
		}
		add_history(line);
		deactivate_signal();
		ret = executor(parser(lexer(line)));
	}
	printf("exit\n");
	return (ret);
}
