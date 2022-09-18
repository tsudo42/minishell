/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:54:42 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:06:40 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/* ************************************************************************** */
/*  This function adds the element ’new_node’ at the end of the list.         */
/* ************************************************************************** */
void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*back;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	back = ft_lstlast(*lst);
	back->next = new_node;
}
