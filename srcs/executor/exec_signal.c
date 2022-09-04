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
	(void)sig;
	write(1, "\n", 1);
}

void	cleanup_exec_signal(void)
{
	errno = 0;
	signal(SIGINT, SIG_IGN);
	if (errno != 0)
	{
		perror(EXEC_INTERNAL_ERRMSG ": signal");
		exit (1);
	}
	return ;
}

void	ready_exec_signal(void)
{
	errno = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (errno != 0)
	{
		cleanup_exec_signal();
		perror(EXEC_INTERNAL_ERRMSG ": signal");
		exit (1);
	}
	return ;
}
