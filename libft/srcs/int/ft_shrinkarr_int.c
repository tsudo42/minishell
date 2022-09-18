/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shrinkarr_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:30:34 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/12 14:46:56 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"
#include "ft_mem.h"
#include <stdlib.h>

int	ft_shrinkarr_int(int *arr, int *sorted_arr, int size)
{
	int	if_malloced;
	int	i;

	if_malloced = 0;
	if (sorted_arr == NULL || \
		(arr <= sorted_arr && arr + size >= sorted_arr) || \
		(sorted_arr <= arr && sorted_arr + size >= arr))
	{
		if_malloced = 1;
		sorted_arr = ft_memdup(arr, sizeof(int) * size);
		if (sorted_arr == NULL)
			return (-1);
		ft_heapsort_int(sorted_arr, size);
	}
	i = 0;
	while (i < size)
	{
		arr[i] = ft_lowerbound_int(arr[i], sorted_arr, size);
		i++;
	}
	if (if_malloced)
		free(sorted_arr);
	return (0);
}
