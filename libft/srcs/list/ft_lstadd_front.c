/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:48:32 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:07:53 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/* ************************************************************************** */
/*  This function adds the element ’new_node’ at the beginning of the list.   */
/*  Even if lst points to NULL, this function lets lst points to new_node.    */
/* ************************************************************************** */
void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	t_list	*tmp;

	if (new_node == NULL || lst == NULL)
		return ;
	tmp = *lst;
	*lst = new_node;
	while (new_node->next != NULL)
		new_node = new_node->next;
	new_node->next = tmp;
}
