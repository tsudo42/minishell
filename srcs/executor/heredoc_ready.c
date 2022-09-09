/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ready.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"

static int	heredoc_ready_d(t_ast_d *d, int *idx, t_environ *env)
{
	int	fd;

	while (d != NULL)
	{
		if (d->type == AST_D_HEREDOC)
		{
			fd = heredoc_set(d->word, idx, env);
			if (fd < 0)
				return (-1);
			(*idx)++;
			d->heredoc_fd = fd;
		}
		d = d->next;
	}
	return (0);
}

static int	heredoc_ready_l(t_ast_l *l, int *idx, t_environ *env)
{
	t_ast_p	*p;

	while (l != NULL)
	{
		p = l->p;
		while (p != NULL)
		{
			if (p->type == AST_P_C)
			{
				if (heredoc_ready_d(p->c->d, idx, env) < 0)
					return (-1);
			}
			else if (p->type == AST_P_S)
			{
				if (heredoc_ready_l(p->s->l, idx, env) < 0 || \
					heredoc_ready_d(p->s->d, idx, env) < 0)
					return (-1);
			}
			p = p->next;
		}
		l = l->next;
	}
	return (0);
}

int	heredoc_ready(t_ast *ast, t_environ *env)
{
	int	idx;

	idx = 0;
	return (heredoc_ready_l(ast, &idx, env));
}
