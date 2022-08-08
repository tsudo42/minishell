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

static bool	is_continue(char	*line)
{
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		printf("line too long\n");
		return (true);
	}
	return (false);
}

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = STATUS_FAILURE;
}

int	main(void)
{
	char *line;
	int		ret;

	line = NULL;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		g_status = 0;
		line = readline("minishell> ");
		if (is_continue(line))
			continue;
		if (line == NULL)
			break ;
		add_history(line);
		ret = executor(parser(lexer(line)));
	}
	printf("exit\n");
	return (ret);
}
