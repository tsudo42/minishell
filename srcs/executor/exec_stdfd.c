/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stdfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"

void	exec_stdfd_set(int *stdfds)
{
	stdfds[0] = ft_x_dup(0, EXEC_ERRMSG);
	stdfds[1] = ft_x_dup(1, EXEC_ERRMSG);
	stdfds[2] = ft_x_dup(2, EXEC_ERRMSG);
}

void	exec_stdfd_reset(int *stdfds)
{
	ft_x_dup2(0, stdfds[0], EXEC_ERRMSG);
	ft_x_dup2(1, stdfds[1], EXEC_ERRMSG);
	ft_x_dup2(2, stdfds[2], EXEC_ERRMSG);
	close(stdfds[0]);
	close(stdfds[1]);
	close(stdfds[2]);
}
