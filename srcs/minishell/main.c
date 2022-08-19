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

#include "minishell.h"

int *exit_status(void)
{
	static int s;

	return (&s);
}

static bool	is_continue(char	*line)
{
	if (!line)
		return (false);
	if (ft_strncmp(line, "\0", 1) == 0)
		return (true);
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		printf("line too long\n");
		return (true);
	}
	return (false);
}

int	main(void)
{
	char *line;
	int		ret;

	line = NULL;
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
