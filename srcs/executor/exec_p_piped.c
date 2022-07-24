/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_p_piped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef struct s_pipe_info {
	pid_t	pid;
	int		fd_in;
	int		fd_out;
}	t_pipe_info;

static t_pipe_info	*infos_ready(size_t	len)
{
	t_pipe_info	*infos;
	size_t		i;
	int			fildes[2];

	infos = ft_x_malloc(sizeof(t_pipe_info) * (len), EXEC_ERRMSG);
	i = 0;
	while (i < len - 1)
	{
		ft_x_pipe(fildes, EXEC_ERRMSG);
		infos[i].fd_out = fildes[1];
		infos[i + 1].fd_in = fildes[0];
		i++;
	}
	infos[0].fd_in = 0;
	infos[len - 1].fd_out = 1;
	return (infos);
}

static void	close_fds(t_pipe_info *infos, size_t len)
{
	size_t	i;

	errno = 0;
	i = 0;
	while (i < len - 1)
	{
		close(infos[i].fd_out);
		close(infos[i + 1].fd_in);
		i++;
	}
	if (errno != 0)
	{
		perror(EXEC_ERRMSG ": close");
		errno = 0;
	}
}

static void	exec_p_piped_child(t_ast_p *p, t_pipe_info *infos, size_t len)
{
	t_pipe_info	*current_info;

	current_info = infos;
	while (current_info->pid != 0)
		current_info++;
	if (current_info->fd_in != 0)
		ft_x_dup2(current_info->fd_in, 0, EXEC_ERRMSG);
	if (current_info->fd_out != 1)
		ft_x_dup2(current_info->fd_out, 1, EXEC_ERRMSG);
	close_fds(infos, len);
	if (p->type == AST_P_C)
		exit(exec_c(p->c));
	exit(exec_s(p->s));
}

static int	exec_p_wait(t_pipe_info *infos, size_t p_len)
{
	int		ret;
	size_t	i;

	i = 0;
	while (i < p_len - 1)
	{
		if (waitpid(infos[i].pid, &ret, WNOHANG) < 0)
		{
			perror(EXEC_ERRMSG ": waitpid");
			errno = 0;
		}
		i++;
	}
	if (waitpid(infos[i].pid, &ret, 0) < 0)
	{
		perror(EXEC_ERRMSG ": waitpid");
		errno = 0;
		ret = 1;
	}
	return (ret);
}

int	exec_p_piped(t_ast_p *p, size_t p_len)
{
	t_pipe_info	*infos;
	size_t		i;
	int			ret;

	infos = infos_ready(p_len);
	i = 0;
	while (p != NULL)
	{
		infos[i].pid = ft_x_fork(EXEC_ERRMSG);
		if (infos[i].pid == 0)
			exec_p_piped_child(p, infos, p_len);
		i++;
		p = p->next;
	}
	close_fds(infos, p_len);
	ret = exec_p_wait(infos, p_len);
	free(infos);
	return (ret);
}
