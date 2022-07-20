/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>

static size_t	count_p_len(t_ast_p *p)
{
	size_t	p_len;

	p_len = 0;
	while (p != NULL)
	{
		p_len++;
		p = p->next;
	}
	return (p_len);
}

static int	exec_p_piped_child(t_ast_p *p, int fildes[2])
{
	ft_x_dup2(0, fildes[0], EXEC_ERRMSG);
	ft_x_dup2(1, fildes[1], EXEC_ERRMSG);
	close(fildes[0]);
	close(fildes[1]);
	if (p->type == AST_P_C)
		return (exec_c(p->c));
	return (exec_s(p->s));
}

static int	exec_p_wait(pid_t *pids, size_t p_len)
{
	int		ret;
	size_t	i;

	i = 0;
	while (i < p_len)
	{
		ft_x_waitpid(pids[i], &ret, 0, EXEC_ERRMSG);
		i++;
	}
	return (ret);
}

static int	exec_p_piped(t_ast_p *p, size_t p_len)
{
	pid_t	*pids;
	size_t	i;
	int		pipe_pair[2];
	int		fd_pair[2];
	int		ret;

	pids = ft_x_malloc(sizeof(pid_t) * p_len, EXEC_ERRMSG);
	i = 0;
	pipe_pair[0] = 0;
	while (p != NULL)
	{
		fd_pair[0] = pipe_pair[0];
		if (p->next == NULL)
			pipe_pair[1] = 1;
		else
			ft_x_pipe(pipe_pair, EXEC_ERRMSG);
		fd_pair[1] = pipe_pair[1];
		pids[i] = ft_x_fork(EXEC_ERRMSG);
		if (pids[i] == 0)
			exec_p_piped_child(p, fd_pair);
		p = p->next;
	}
	ret = exec_p_wait(pids, p_len);
	free(pids);
	return (ret);
}

int	exec_p(t_ast_p *p)
{
	size_t	p_len;

	if (p == NULL)
		exec_error("p is NULL");
	p_len = count_p_len(p);
	if (p_len == 1 && p->type == AST_P_C)
		return (exec_c(p->c));
	return (exec_p_piped(p, p_len));
}
