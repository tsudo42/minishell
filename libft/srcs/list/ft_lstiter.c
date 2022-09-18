/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:13:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:08:52 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/* ************************************************************************** */
/*  This function iterates the list ’lst’ and applies the function ’f’ to     */
/*  the content of each element.                                              */
/* ************************************************************************** */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
