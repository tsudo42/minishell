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

#include "environ.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MINISHELL_HEREDOC_FILENO 3
#define MAIN_ERRMSG "minishell"

static void	init(void)
{
	set_exit_status(0);
	if (ft_init_environ() < 0)
		exit(2);
	if (dup2(STDERR_FILENO, MINISHELL_HEREDOC_FILENO) < 0)
	{
		perror(MAIN_ERRMSG ": init: dup2");
		exit(2);
	}
}

static char	*input(void)
{
	write(1, "> ", 2);
	return (get_next_line(0));
}

int	main(void)
{
	char	*line;
	int		ret;

	ret = 0;
	set_exit_status(0);
	write(1, "> ", 2);
	line = get_next_line(0);
	while (line != NULL)
	{
		ret = executor(parser(lexer(line)));
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	return (ret);
}
