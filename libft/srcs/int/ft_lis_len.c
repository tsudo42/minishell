/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lis_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:32:27 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/23 16:32:27 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function returns the length of LIS;Longest Increasing Subsequence.   */
/*  Only when malloc(3) fails, this function returns 0.                       */
/* ************************************************************************** */
size_t	ft_lis_len(const int *arr, size_t size)
{
	size_t	i;
	size_t	lis_size;
	int		*lis;

	if (arr == NULL || size == 0)
		return (0);
	lis = malloc(sizeof(int) * size);
	if (lis == NULL)
		return (0);
	lis[0] = arr[0];
	lis_size = 1;
	i = 1;
	while (i < size)
	{
		if (lis[lis_size - 1] < arr[i])
			lis[lis_size++] = arr[i];
		else
			lis[ft_lowerbound_int(arr[i], lis, lis_size)] = arr[i];
		i++;
	}
	free(lis);
	return (lis_size);
}
