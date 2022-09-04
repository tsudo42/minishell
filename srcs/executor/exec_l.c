/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>

int	exec_l(t_ast_l *l, t_environ *env)
{
	int	ret;

	if (l == NULL)
		exec_error("l is NULL");
	ret = exec_p(l->p, env);
	env->exit_status = ret;
	l = l->next;
	while (l != NULL)
	{
		if (!(ret) ^ (l->op == AST_L_OR))
		{
			ret = exec_p(l->p, env);
			env->exit_status = ret;
		}
		l = l->next;
	}
	return (ret);
}
