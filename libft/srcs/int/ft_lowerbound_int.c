/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerbound_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:35:55 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/05 23:19:28 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"

/* ************************************************************************** */
/*  This function returns the index of key in sorted_arr if exists.           */
/*  Otherwise, returns idx where sorted_arr[idx-1] < key < sorted_arr[idx].   */
/*  The idx can be equal to size, when key is bigger than any num in arr, so  */
/*  be careful using return value as an index of the original arr.            */
/* ************************************************************************** */
size_t	ft_lowerbound_int(int key, int *sorted_arr, size_t size)
{
	size_t	left;
	size_t	right;
	size_t	mid;

	if (size == 0)
		return (1);
	left = 0;
	right = size;
	while (left + 1 < right)
	{
		mid = left + (right - left) / 2;
		if (key <= sorted_arr[mid])
			right = mid;
		else
			left = mid;
	}
	if (left <= right && key <= sorted_arr[left])
		return (left);
	return (right);
}
