/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/26 18:13:42 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	deactivate_signal_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	return ;
}

int	rl_status_checker_heredoc(void)
{
	if (g_sig != 0)
	{
		rl_event_hook = 0;
		rl_done = 1;
	}
	return (0);
}

static void	signal_handler_heredoc(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	set_exit_status(130);
	return ;
}

void	activate_signal_heredoc(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
