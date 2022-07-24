/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_p.c                                            :+:      :+:    :+:   */
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

static t_ast_p	*ast_make_p_s(t_ast_p *prev_p, t_ast_s *s)
{
	t_ast_p			*p;
	t_ast_p			*prev_p_head;

	p = malloc(sizeof(t_ast_p));
	if (p == NULL)
	{
		ast_free_p(prev_p);
		ast_free_s(s);
		return (NULL);
	}
	p->type = AST_P_S;
	p->s = s;
	p->c = NULL;
	p->next = NULL;
	if (prev_p == NULL)
		return (p);
	prev_p_head = prev_p;
	while (prev_p->next != NULL)
		prev_p = prev_p->next;
	prev_p->next = p;
	return (prev_p_head);
}

static t_ast_p	*ast_make_p_c(t_ast_p *prev_p, t_ast_c *c)
{
	t_ast_p			*p;
	t_ast_p			*prev_p_head;

	p = malloc(sizeof(t_ast_p));
	if (p == NULL)
	{
		ast_free_p(prev_p);
		ast_free_c(c);
		return (NULL);
	}
	p->type = AST_P_C;
	p->s = NULL;
	p->c = c;
	p->next = NULL;
	if (prev_p == NULL)
		return (p);
	prev_p_head = prev_p;
	while (prev_p->next != NULL)
		prev_p = prev_p->next;
	prev_p->next = p;
	return (prev_p_head);
}

t_ast_p	*ast_make_p(t_ast_p *prev_p, t_ast_p_type type, void *content)
{
	if (content == NULL)
	{
		ast_free_p(prev_p);
		return (NULL);
	}
	if (type == AST_P_S)
		return (ast_make_p_s(prev_p, content));
	if (type == AST_P_C)
		return (ast_make_p_c(prev_p, content));
	ast_free_p(prev_p);
	free(content);
	return (NULL);
}

void	ast_free_p(t_ast_p *p)
{
	t_ast_p	*prev_p;

	while (p != NULL)
	{
		ast_free_s(p->s);
		ast_free_c(p->c);
		prev_p = p;
		p = p->next;
		free(prev_p);
	}
}
