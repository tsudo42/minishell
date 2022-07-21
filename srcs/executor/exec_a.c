/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>

static size_t	count_args(t_ast_a *a)
{
	size_t	count;

	count = 0;
	while (a != NULL)
	{
		count++;
		a = a->next;
	}
	return (count);
}

char	**exec_a(t_ast_a *a)
{
	char	**args;
	size_t	i;

	args = ft_x_malloc(sizeof(char *) * (count_args(a) + 1), EXEC_ERRMSG);
	i = 0;
	while (a != NULL)
	{
		args[i] = expander(a->word);
		a = a->next;
		i++;
	}
	args[i] = NULL;
	return (args);
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
