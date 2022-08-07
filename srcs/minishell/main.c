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

bool	ft_is_continue(char	*line)
{
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		printf("line too long\n");
		return (true);
	}
	return (false);
}

void	ft_signal_handler(int sig)
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
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		g_status = 0;
		line = readline("minishell> ");
		if (ft_is_continue(line))
			continue;
		if (line == NULL)
			break ;
		ret = executor(parser(lexer(line)));
		add_history(line);
//		free(line); // has to be deleted when the compilation with lexer.
	}
//	free(line); // has to be deleted when the compilation with lexer.
	printf("exit\n");
	return (ret);
}
