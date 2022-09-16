/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 16:53:54 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

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
}

void	cleanup_heredoc_signal(int *is_error)
{
	rl_event_hook = 0;
	errno = 0;
	ft_x_signal(SIGINT, SIG_IGN, EXEC_ERRMSG ": signal");
	if (errno != 0)
		*is_error = 1;
}

int	ready_heredoc_signal(int *is_error)
{
	errno = 0;
	ft_x_signal(SIGINT, signal_handler_heredoc, EXEC_ERRMSG ": signal");
	ft_x_signal(SIGQUIT, SIG_IGN, EXEC_ERRMSG ": signal");
	if (errno != 0)
	{
		*is_error = 1;
		cleanup_heredoc_signal(is_error);
		return (-1);
	}
	rl_event_hook = rl_status_checker_heredoc;
	return (0);
}
