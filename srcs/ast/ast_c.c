/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"
#include "libft.h"
#include <stdlib.h>

t_ast_c	*ast_make_c(t_ast_c *c, t_ast_a *a, t_ast_d *d)
{
	if (c == NULL)
	{
		c = malloc(sizeof(t_ast_c));
		if (c == NULL)
		{
			ast_free_a(a);
			ast_free_d(d);
			return (NULL);
		}
		c->a = NULL;
		c->d = NULL;
	}
	c->a = ast_join_a(c->a, a);
	c->d = ast_join_d(c->d, d);
	return (c);
}

void	ast_free_c(t_ast_c *c)
{
	if (c == NULL)
		return ;
	ast_free_a(c->a);
	ast_free_d(c->d);
	free(c);
}
