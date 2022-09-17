/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:46:17 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ARG_MAX_SIZE 4096

int	cleanup_signal(void);
int	ready_signal(void);

static int	is_continue(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "\0", 1) == 0)
		return (1);
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		ft_putendl_fd(ERRMSG ": line too long", STDERR_FILENO);
		return (1);
	}
	return (0);
}

char	*input(t_environ *env)
{
	char	*line;

	while (1)
	{
		errno = 0;
		g_sig = 0;
		ready_signal();
		line = readline("minishell> ");
		cleanup_signal();
		if (g_sig != 0)
		{
			free(line);
			env->exit_status = 130;
			continue ;
		}
		if (is_continue(line))
			continue ;
		add_history(line);
		return (line);
	}
}
