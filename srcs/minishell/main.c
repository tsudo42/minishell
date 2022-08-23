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

#define MAIN_ERRMSG "minishell"

static int	init(void)
{
	set_exit_status(0);
	if (ft_init_environ() < 0)
		exit(2);
	return (0);
}

static char	*input(void)
{
	write(STDERR_FILENO, "> ", 2);
	return (get_next_line(0));
}

int	main(void)
{
	char	*line;
	int		ret;

	ret = init();
	line = input();
	while (line != NULL)
	{
		ret = executor(parser(lexer(line)));
		line = input();
	}
	return (ret);
}
