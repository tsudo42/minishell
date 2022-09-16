/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:05:12 by hos               #+#    #+#             */
/*   Updated: 2022/09/16 09:00:49 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	do_swap(t_var **var, long *swap_count)
{
	t_var	*tmp;

	if (ft_strcmp((*var)->key, (*var)->next->key) > 0)
	{
		tmp = (*var)->next;
		(*var)->next = tmp->next;
		tmp->next = (*var);
		(*var) = tmp;
		(*swap_count)++;
		return (1);
	}
	return (0);
}

void	builtin_export_sort(t_environ *env)
{
	t_var	*var;
	t_var	*prev;
	long	i;
	long	swap_count;

	swap_count = -1;
	while (swap_count != 0)
	{
		swap_count = 0;
		i = 0;
		var = env->vars;
		prev = NULL;
		while (var->next != NULL)
		{
			if (do_swap(&var, &swap_count) && i == 0)
				env->vars = var;
			if (prev)
				prev->next = var;
			prev = var;
			var = var->next;
			i++;
		}
	}
}
