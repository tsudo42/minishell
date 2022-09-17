/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:05:12 by hos               #+#    #+#             */
/*   Updated: 2022/09/17 19:08:25 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmp_key(void *p1, void *p2)
{
	t_var	*v1;
	t_var	*v2;

	v1 = p1;
	v2 = p2;
	return (ft_strcmp(v1->key, v2->key));
}

t_list	*init_list(t_environ *env)
{
	t_list	*list;
	t_list	*list2;
	t_var	*var;

	if (!env)
		return (NULL);
	var = env->vars;
	list = ft_lstnew(var);
	if (!list)
		ft_x_perror(EXIT_ERRMSG ": malloc");
	if (var->next != NULL)
		var = var->next;
	while (var != NULL)
	{
		list2 = ft_lstnew(var);
		if (!list2)
			ft_x_perror(EXIT_ERRMSG ": malloc");
		ft_lstadd_back(&list, list2);
		var = var->next;
	}
	return (list);
}
