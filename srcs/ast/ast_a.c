/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_a.c                                            :+:      :+:    :+:   */
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

t_ast_a	*ast_join_a(t_ast_a *a_head, t_ast_a *a_tail)
{
	t_ast_a	*a_head_ret;

	if (a_head == NULL)
		return (a_tail);
	a_head_ret = a_head;
	while (a_head->next != NULL)
		a_head = a_head->next;
	a_head->next = a_tail;
	return (a_head_ret);
}

t_ast_a	*ast_make_a(char *red, char *word)
{
	t_ast_a	*a;

	a = malloc(sizeof(t_ast_a));
	if (a == NULL)
	{
		free(red);
		free(word);
		return (NULL);
	}
	a->red = red;
	a->word = word;
	a->next = NULL;
	return (a);
}

void	ast_free_a(t_ast_a *a)
{
	t_ast_a	*prev_a;

	while (a != NULL)
	{
		free(a->red);
		free(a->word);
		prev_a = a;
		a = a->next;
		free(prev_a);
	}
}
