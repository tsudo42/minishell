/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ast_internal.h"
#include "utils.h"
#include "libft.h"
#include <stdlib.h>

static t_ast_d_type	extract_ast_d_type(char *red_str)
{
	t_ast_d_type	type;

	while (ft_isdigit(*red_str))
		red_str++;
	if (ft_strncmp("<", red_str, sizeof("<")) == 0)
		type = AST_D_REDIN;
	else if (ft_strncmp(">>", red_str, sizeof(">>")) == 0)
		type = AST_D_REDAPP;
	else if (ft_strncmp(">", red_str, sizeof(">")) == 0)
		type = AST_D_REDOUT;
	else
		type = AST_D_HEREDOC;
	*red_str = '\0';
	return (type);
}

/* errno should be zero. */
t_ast_d	*ast_convert_a_to_d(t_ast_a *a)
{
	t_ast_d	*d;

	if (errno != 0 || a == NULL)
	{
		ast_free_a(a);
		return (NULL);
	}
	d = malloc(sizeof(t_ast_d));
	if (d == NULL)
	{
		ast_free_a(a);
		return (NULL);
	}
	d->num = a->red;
	d->word = a->word;
	d->type = extract_ast_d_type(d->num);
	d->heredoc_fd = -1;
	d->next = ast_convert_a_to_d(a->next);
	a->next = NULL;
	if (d->next == NULL && errno != 0)
	{
		ast_free_d(d);
		return (NULL);
	}
	return (d);
}

t_ast_d	*ast_join_d(t_ast_d *d_head, t_ast_d *d_tail)
{
	t_ast_d	*d_head_ret;

	if (d_head == NULL)
		return (d_tail);
	d_head_ret = d_head;
	while (d_head->next != NULL)
		d_head = d_head->next;
	d_head->next = d_tail;
	return (d_head_ret);
}

t_ast_d	*ast_make_d(t_ast_d *prev_d, char *red, char *word)
{
	t_ast_d	*d;

	d = malloc(sizeof(t_ast_d));
	if (d == NULL)
	{
		free(red);
		free(word);
		return (NULL);
	}
	d->num = red;
	d->word = word;
	d->type = extract_ast_d_type(d->num);
	d->heredoc_fd = -1;
	d->next = NULL;
	if (prev_d == NULL)
		return (d);
	return (ast_join_d(prev_d, d));
}

void	ast_free_d(t_ast_d *d)
{
	t_ast_d	*prev_d;

	while (d != NULL)
	{
		free(d->num);
		free(d->word);
		if (d->heredoc_fd >= 0)
			close(d->heredoc_fd);
		d->heredoc_fd = -1;
		prev_d = d;
		d = d->next;
		free(prev_d);
	}
}
