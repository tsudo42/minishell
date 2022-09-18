/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:58:34 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:08:21 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function deletes and frees the given element and every successor     */
/*  of that element, using the function ’del’ and free(3).                    */
/*  Finally, the pointer to the list is set to NULL.                          */
/* ************************************************************************** */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	if (del != NULL)
	{
		while ((*lst) != NULL)
		{
			next_tmp = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = next_tmp;
		}
		return ;
	}
	while ((*lst) != NULL)
	{
		next_tmp = (*lst)->next;
		free(*lst);
		*lst = next_tmp;
	}
}

/* ************************************************************************** */
/*  The line 30 ~ 38 and 40 ~ 46 are almost the same.                         */
/*  In order to reduce the time to judge the if condition, the author of the  */
/*  function duplicated that lines.                                           */
/* ************************************************************************** */
