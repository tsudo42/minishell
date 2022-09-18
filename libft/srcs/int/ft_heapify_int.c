/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heapify_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:45:10 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/05 16:23:56 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"

/* ************************************************************************** */
/*  This function rearrange lst so that the lst maintains the heap property.  */
/* ************************************************************************** */
void	ft_heapify_int(int *lst, int size)
{
	int	i;
	int	tmp;
	int	parent;
	int	current_size;

	current_size = 0;
	while (current_size < size)
	{
		i = current_size;
		while (i > 0)
		{
			parent = (i + 1) / 2 - 1;
			if (lst[i] > lst[parent])
			{
				tmp = lst[i];
				lst[i] = lst[parent];
				lst[parent] = tmp;
			}
			i = parent;
		}
		current_size++;
	}
}
