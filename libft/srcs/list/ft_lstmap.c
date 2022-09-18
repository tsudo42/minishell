/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:14:26 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:09:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This helper function creates the front of a new list of results from      */
/*  f(lst->content) using malloc(3).                                          */
/* ************************************************************************** */
static t_list	*ft_lstmap_front(t_list *lst, void *(*f)(void *))
{
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (f == NULL)
		new->content = NULL;
	else
		new->content = f(lst->content);
	new->next = NULL;
	return (new);
}

/* ************************************************************************** */
/*  This function iterates the list ’lst’ and applies the function ’f’ to     */
/*  the content of each element,                                              */
/*  and creates a new list resulting of the successive applications of the    */
/*  function ’f’ using malloc(3).                                             */
/*  If `content` is NULL, the content of each new lst will be NULL.           */
/*  The ’del’ function is used to delete the content of an element            */
/*  if malloc(3) fails.                                                       */
/* ************************************************************************** */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_front;

	new_front = ft_lstmap_front(lst, f);
	if (new_front == NULL)
		return (NULL);
	new = new_front;
	while (lst->next != NULL)
	{
		lst = lst->next;
		new->next = (t_list *)malloc(sizeof(t_list));
		if (new->next == NULL)
		{
			ft_lstclear(&new_front, del);
			return (NULL);
		}
		new = new->next;
		if (f == NULL)
			new->content = NULL;
		else
			new->content = f(lst->content);
	}
	new->next = NULL;
	return (new_front);
}
