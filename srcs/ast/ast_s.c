/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_s.c                                            :+:      :+:    :+:   */
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

t_ast_s	*ast_make_s(t_ast_l *l, t_ast_d *d)
{
	t_ast_s	*s;

	s = malloc(sizeof(t_ast_s));
	if (s == NULL)
	{
		ast_free_l(l);
		ast_free_d(d);
		return (NULL);
	}
	s->l = l;
	s->d = d;
	return (s);
}

void	ast_free_s(t_ast_s *s)
{
	if (s == NULL)
		return ;
	ast_free_l(s->l);
	ast_free_d(s->d);
	free(s);
}
