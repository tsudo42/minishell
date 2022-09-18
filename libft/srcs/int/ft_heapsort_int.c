/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heapsort_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:34:04 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/05 16:48:06 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"

/* tree node n: <left=2(n + 1) - 1> <right=2(n + 1)> <root=(n + 1)/2 - 1> */
/* 0: <left=1> <right=2> <root=-1>*/
/* 1: <left=3> <right=4> <root=0> */
/* 2: <left=5> <right=6> <root=0> */
/* 3: <left=7> <right=8> <root=1> */
/*
 *                 0
 *               /   \
 *             1       2
 *            / \     / \
 *           3   4   5   6
 */

static void	ft_downheap_helper(int *lst, int size)
{
	int	i;
	int	next;
	int	tmp;

	i = 0;
	while (1)
	{
		if (2 * (i + 1) - 1 >= size)
			return ;
		next = 2 * (i + 1) - 1;
		if (next + 1 < size && lst[next] < lst[next + 1])
			next++;
		if (lst[i] < lst[next])
		{
			tmp = lst[i];
			lst[i] = lst[next];
			lst[next] = tmp;
		}
		else
			return ;
		i = next;
	}
}

/* ************************************************************************** */
/*  This function sorts the array of ints in ascending order using heapsort.  */
/* ************************************************************************** */
void	ft_heapsort_int(int *lst, int size)
{
	int	tmp;

	if (size <= 0)
		return ;
	ft_heapify_int(lst, size);
	while (--size > 0)
	{
		tmp = lst[size];
		lst[size] = lst[0];
		lst[0] = tmp;
		ft_downheap_helper(lst, size);
	}
}
