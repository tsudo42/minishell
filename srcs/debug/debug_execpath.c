/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_execpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "debug.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Function to debug execpath().
 * Input via stdin and print the result of execpath.
 * Always returns 0.
 */
int	debug_execpath(void)
{
	t_environ	*env;
	char		*input;
	char		*path;
	int			save_errno;

	env = init_environ();
	write(1, "> ", 2);
	input = get_next_line_easy(0);
	while (input != NULL)
	{
		errno = 0;
		path = execpath(ft_trimnl(input), env);
		save_errno = errno;
		printf("execpath: %s\n", path);
		if (save_errno != 0)
			printf("(%s)\n", strerror(save_errno));
		free(path);
		free(input);
		write(1, "> ", 2);
		input = get_next_line_easy(0);
	}
	destroy_environ(env);
	return (0);
}
