/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 08:34:16 by hos               #+#    #+#             */
/*   Updated: 2022/09/04 09:07:41 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"

static void	signal_handler(int sig)
{
	g_sig = sig;
}

void	ready_exec_signal(void)
{
	errno = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (errno != 0)
	{
		cleanup_exec_signal();
		perror(EXEC_INTERNAL_ERRMSG ": signal");
		exit (1);
	}
	return ;
}
