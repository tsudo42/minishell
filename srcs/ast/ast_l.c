/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"
#include <stdlib.h>

t_ast_l	*ast_make_l(t_ast_l *prev_l, t_ast_l_type op, t_ast_p *p)
{
	t_ast_l	*l;
	t_ast_l	*prev_l_head;

	l = malloc(sizeof(t_ast_l));
	if (l == NULL)
	{
		ast_free_l(prev_l);
		ast_free_p(p);
		return (NULL);
	}
	l->op = op;
	l->p = p;
	l->next = NULL;
	if (prev_l == NULL)
		return (l);
	prev_l_head = prev_l;
	while (prev_l->next != NULL)
		prev_l = prev_l->next;
	prev_l->next = l;
	return (prev_l_head);
}

void	ast_free_l(t_ast_l *l)
{
	t_ast_l	*prev_l;

	while (l != NULL)
	{
		ast_free_p(l->p);
		prev_l = l;
		l = l->next;
		free(prev_l);
	}
}
