/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	**lst_to_strs(t_list *lst)
{
	char	**strs;
	size_t	i;
	t_list	*tmp;

	strs = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (strs == NULL)
	{
		perror(EXEC_ERRMSG ": malloc");
		ft_lstclear(&lst, free);
		return (NULL);
	}
	i = 0;
	while (lst != NULL)
	{
		strs[i] = lst->content;
		tmp = lst->next;
		free(lst);
		lst = tmp;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

char	**exec_a(t_ast_a *a, t_environ *env)
{
	t_list	*lst;
	t_list	*lst_node;

	errno = 0;
	lst = NULL;
	while (a != NULL)
	{
		lst_node = expander(a->word, env);
		a->word = NULL;
		if (lst_node == NULL && errno != 0)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, lst_node);
		a = a->next;
	}
	return (lst_to_strs(lst));
}
