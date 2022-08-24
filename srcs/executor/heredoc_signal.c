/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/24 11:22:40 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void deactivate_signal_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	return ;
}

static void	signal_handler_heredoc(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	exit (130);
//	exit (*exit_status() = 130);
}

void	activate_signal_heredoc(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
