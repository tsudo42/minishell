/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_calc_retval.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <sys/wait.h>
#include <signal.h>

static int	exec_signaled_prompt(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		ft_dprintf(STDERR_FILENO, "Quit: %d\n", sig);
	}
	return (0);
}

int	exec_calc_retval(int stat, t_environ *env)
{
	pid_t	pid;

	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	if (WIFSIGNALED(stat))
	{
		g_sig = WTERMSIG(stat);
		pid = getpid();
		if (pid > 0 && pid != env->parent_pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			kill(pid, WTERMSIG(stat));
			perror("kill");
		}
		else
			exec_signaled_prompt(g_sig);
		return (WTERMSIG(stat) + 128);
	}
	return (WSTOPSIG(stat) + 128);
}
