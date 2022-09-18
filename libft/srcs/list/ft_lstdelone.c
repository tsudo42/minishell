/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:56:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:08:34 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function takes as a parameter an element and frees the memory of     */
/*  the element’s content using the function ’del’ given as a parameter and   */
/*  free the element.                                                         */
/*  The memory of ’next’ will not be freed.                                   */
/* ************************************************************************** */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del != NULL)
		del(lst->content);
	lst->content = NULL;
	lst->next = NULL;
	free(lst);
}
