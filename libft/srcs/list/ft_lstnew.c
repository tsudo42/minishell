/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:24:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:09:24 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function allocates (with malloc(3)) and returns a new element.       */
/*  The variable ’content’ is initialized with the value of the parameter     */
/*  ’content’.  The variable ’next’ is initialized to NULL.                   */
/* ************************************************************************** */
t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr != NULL)
	{
		ptr->content = content;
		ptr->next = NULL;
	}
	return (ptr);
}
