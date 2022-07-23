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
