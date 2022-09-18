/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:19:16 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:51:35 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function allocates memory with its size of count*size, set 0 to the  */
/*  allocated memory, and returns the pointer to beginning of the memory.     */
/*  if count * size equals to 0, the behaviour is undefined (allocates 1).    */
/*  if count * size overflows, the behaviour is undefined (allocates 1).      */
/* ************************************************************************** */
void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ret;

	total_size = count * size;
	if (total_size <= 0)
		total_size = 1;
	ret = malloc(total_size);
	if (ret != NULL)
		ft_memset(ret, 0, total_size);
	return (ret);
}
