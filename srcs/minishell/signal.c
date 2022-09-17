/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:46:08 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <readline/readline.h>

static int	rl_status_checker(void)
{
	if (g_sig != 0)
	{
		rl_event_hook = 0;
		rl_done = 1;
	}
	return (0);
}

static void	signal_handler(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
}

int	cleanup_signal(void)
{
	rl_event_hook = 0;
	errno = 0;
	ft_x_signal(SIGINT, SIG_IGN, ERRMSG ": signal");
	if (errno != 0)
		return (-1);
	return (0);
}

int	ready_signal(void)
{
	errno = 0;
	ft_x_signal(SIGINT, signal_handler, ERRMSG ": signal");
	ft_x_signal(SIGQUIT, SIG_IGN, ERRMSG ": signal");
	if (errno != 0)
	{
		cleanup_signal();
		return (-1);
	}
	rl_event_hook = rl_status_checker;
	return (0);
}
