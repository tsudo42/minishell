/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"

static void	exec_pid_error(const char *func_name)
{
	if (func_name == NULL)
		func_name = "unknown";
	ft_dprintf(STDERR_FILENO, \
		"%s: %s: %s", EXEC_INTERNAL_ERRMSG, func_name, strerror(errno));
	exit(EXEC_INTERNAL_ERRNUM);
}

static void	exec_pid_tell(int fifo[2], pid_t pid)
{
	if (close(fifo[0]) < 0)
		exec_pid_error("close");
	if (write(fifo[1], &pid, sizeof(pid_t)) < 0)
		exec_pid_error("write");
	if (close(fifo[1]) < 0)
		exec_pid_error("close");
}

static pid_t	exec_pid_recv(int fifo[2])
{
	pid_t	pid;

	if (close(fifo[1]) < 0)
		exec_pid_error("close");
	if (read(fifo[0], &pid, sizeof(pid_t)) < 0)
		exec_pid_error("read");
	if (close(fifo[0]) < 0)
		exec_pid_error("close");
	return (pid);
}

pid_t	exec_fork(t_environ *env)
{
	int		fifo[2];
	pid_t	pid;

	if (pipe(fifo) < 0)
		exec_pid_error("pipe");
	pid = fork();
	if (pid < 0)
		exec_pid_error("fork");
	if (pid != 0)
		exec_pid_tell(fifo, pid);
	else
		env->my_pid = exec_pid_recv(fifo);
	return (pid);
}
