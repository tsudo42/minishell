/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/26 17:38:22 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
}

int	rl_status_checker(void)
{
	if (g_sig != 0)
	{
		rl_event_hook = 0;
		rl_done = 1;
	}
	return (0);
}

void	activate_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	deactivate_signal(void)
{
	signal(SIGINT, SIG_IGN);
	return ;
}
