/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"

static int	heredoc_set_d(t_ast_d *d, int *count)
{
	int	fd;

	while (d != NULL)
	{
		if (d->type == AST_D_HEREDOC)
		{
			fd = ready_heredoc(d->word, *count);
			if (fd < 0)
				return (-1);
			(*count)++;
			d->heredoc_fd = fd;
		}
		d = d->next;
	}
	return (0);
}

static int	heredoc_set_l(t_ast_l *l, int *count)
{
	t_ast_p	*p;

	while (l != NULL)
	{
		p = l->p;
		while (p != NULL)
		{
			if (p->type == AST_P_C)
			{
				if (heredoc_set_d(p->c->d, count) < 0)
					return (-1);
			}
			else if (p->type == AST_P_S)
			{
				if (heredoc_set_l(p->s->l, count) < 0 || \
					heredoc_set_d(p->s->d, count) < 0)
					return (-1);
			}
			p = p->next;
		}
		l = l->next;
	}
	return (0);
}

int	heredoc_set(t_ast *ast)
{
	int	count;

	count = 0;
	return (heredoc_set_l(ast, &count));
}
