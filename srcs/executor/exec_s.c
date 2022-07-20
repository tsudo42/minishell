/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"

int	exec_s(t_ast_s *s)
{
	int	stdfds[3];
	int	ret;

	if (s == NULL)
		exec_error("s is NULL");
	exec_stdfd_set(stdfds);
	if (exec_d(s->d) != 0)
	{
		exec_stdfd_reset(stdfds);
		return (1);
	}
	ret = exec_l(s->l);
	exec_stdfd_reset(stdfds);
	return (ret);
}
